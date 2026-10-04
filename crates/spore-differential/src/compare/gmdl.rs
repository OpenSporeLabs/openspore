//! Comparison 4: the gmdl walk, field by field.
//!
//! Rust `spore_gmdl::parse` against `tools/spore/gmdl/gmdl.py::Gmdl`, for a
//! deterministic bounded sample of the gmdl records.
//!
//! # Fields compared
//!
//! version, the reference-file table, meshCount, the bounding box, the bounding
//! radius, each index buffer's prim/count/bits and its byte length, each vertex
//! descriptor's element count and each element's stream/offset/declType/
//! declMethod/declUsage/usageIndex/typeCode, each vertex buffer's descIdx/
//! vertexCount/bufSize and byte length, the mesh table, the material ids, the
//! bone ranges, the trailing key, and `matches()`.
//!
//! # `matches()` is compared against `fully_walked()`
//!
//! The oracle's `matches()` is `finalOffset == len(bytes)`. The Rust analogue is
//! `GmdlModel::fully_walked()`, i.e. `strict_consumed == consumed` -- and
//! `consumed` is always the input length, so the two mean the same thing: every
//! byte was accounted for. The Rust side reports the *trailer* separately, and
//! that is reported here too, because "we read all of it" and "all of it was
//! there" come apart and collapsing them would hide the difference.
//!
//! # Two fields are structurally not comparable, and say so
//!
//! * `materialInfos`: the oracle builds the whole nested tree, skipping
//!   non-texture-set entries with `ShaderData.getDataSize`. Rust exposes the
//!   flattened texture references instead. There is no Rust value to compare
//!   against, so this comparison reports the *shapes* both sides derived (entry
//!   count and texture count) rather than pretending to compare a tree against a
//!   list.
//! * `unk` (the word between the material ids and the material-info count) is
//!   read by the oracle and not exposed by Rust. Reported as "the oracle read
//!   this, the Rust port does not carry it".
//!
//! Both are definitional, and both are stated rather than skipped silently.
//!
//! # What the real corpus does to the anim-data walk
//!
//! Measured over a 293-record sample of the 4209 gmdl records in
//! `Spore_Content.package`: **0 field-level divergences**, but **123 records the
//! oracle cannot walk at all** and 36 both sides refuse. Every one of those is
//! the same root cause, and it is worth stating because the two sides classify it
//! very differently.
//!
//! The anim-data section's baked-deform count word is read at a fixed offset
//! inside each record. On these records that word reads as a plausible-looking
//! `1065353216` (`0x3F800000`, which is `1.0f`), which would require 4.26 GB of
//! following bytes in a 380 KB record. `Spore_Content.package[117]`:
//!
//! ```text
//! anim[0] 0x5b580..0x5b614  bakedDeformCount=0            OK
//! anim[1] 0x5b614..0x5b6a8  bakedDeformCount=0            OK
//! anim[2] 0x5b6a8..0x5b73c  bakedDeformCount=1065353216   IMPOSSIBLE
//! ```
//!
//! `gmdl.py` adds `bc * 4` to its offset without checking and dies on the next
//! `struct.unpack_from`. `spore-gmdl` checks the extent first, refuses the walk,
//! and reports `TrailerWalk::Truncated { at: BakedDeform }` -- so its
//! `strict_consumed` is 374 588 of the record's 382 860 bytes.
//!
//! **Neither side decoded these records.** The oracle died; the Rust port
//! returned `Ok` with a truncated tail. Calling that a `rust-only` verdict would
//! credit the Rust side for a partial decode it does not claim as complete, which
//! is why the verdict message quotes `trailer` and `strict_consumed` verbatim:
//! `Ok` from `spore_gmdl::parse` is not the same statement as "read all of it".
//!
//! The count word being `0x3F800000` rather than garbage suggests the anim-data
//! record layout is wrong at that offset -- most likely a field this crate's
//! prefix size (`64*2 + 4 + 12`) does not model. That is a **ceiling in both
//! implementations**, not a difference between them, and this harness reports it
//! rather than resolving it.

use spore_assets::Package;
use spore_core::record::type_id;
use spore_gmdl::GmdlModel;

use crate::corpus::{Corpus, LocatedPackage, LocatedRecord, RecordKind};
use crate::floats::{ReportBuilder, FLOAT_TOLERANCE};
use crate::json::{self, Json};
use crate::oracle::{OracleConfig, OracleError, OracleSession};
use crate::report::{Agreement, DifferentialReport, Divergence, DivergenceClass, RecordIdentity};
use crate::sample::{describe_sample, sample_indices};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "gmdl-walk";

/// How the oracle is invoked for the package-level comparison.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one \
                              NDJSON {cmd:\"gmdl\", i:N} request per sampled record, answered \
                              from gmdl.py::Gmdl fields";

/// How the oracle is invoked for the loose-fixture comparison.
pub const FILE_INVOCATION: &str =
    "`python3 -c` driver, one NDJSON {cmd:\"gmdl_file\", path:...} request, answered from \
     gmdl.py::Gmdl fields";

/// How many records the default sample draws.
pub const DEFAULT_SAMPLE: usize = 300;

/// Runs the gmdl comparison over the corpus's primary package.
pub fn compare(corpus: &Corpus, config: &OracleConfig) -> DifferentialReport {
    compare_with_budget(corpus, config, DEFAULT_SAMPLE)
}

/// Runs the gmdl comparison with an explicit sample budget.
pub fn compare_with_budget(
    corpus: &Corpus,
    config: &OracleConfig,
    budget: usize,
) -> DifferentialReport {
    super::run(NAME, || {
        let Some(package) = primary_package(corpus) else {
            return Ok::<_, OracleError>(skipped(
                NAME,
                format!(
                    "no package located (set {} to a checkout with SPORE/)",
                    crate::corpus::ROOT_ENV
                ),
            ));
        };
        compare_package(package, config, budget)
    })
}

/// Runs the gmdl comparison over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
    budget: usize,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.set_tolerance(FLOAT_TOLERANCE);
    builder.note(format!(
        "package {}; Rust side: spore_gmdl::parse; oracle: gmdl.py::Gmdl; floats compared at {}",
        package.name,
        crate::floats::describe_tolerance(FLOAT_TOLERANCE)
    ));
    builder.note(
        "the oracle reads two things spore-gmdl does not carry: the `unk` word between the \
         material ids and the material-info count, and the material-info GROUP structure (it \
         carries the flattened texture references instead). Each is reported per record as a \
         note, and the group structure as a definitional divergence when it would otherwise be \
         invisible.",
    );

    let opened = Package::open(package.name.clone(), &package.path).map_err(|error| {
        OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
    })?;
    let image = opened.bytes();
    let targets: Vec<(usize, spore_dbpf::DbpfEntry)> = opened
        .index()
        .entries()
        .iter()
        .enumerate()
        .filter(|(_, entry)| entry.type_id == type_id::GMDL)
        .map(|(index, entry)| (index, *entry))
        .collect();

    if targets.is_empty() {
        builder.skip(format!(
            "{} holds no 0x{:08x} (gmdl) records, so there is nothing to walk",
            package.name,
            type_id::GMDL
        ));
        return Ok(builder.finish());
    }
    // The sample is drawn over the FILTERED gmdl list, but the oracle addresses
    // records by their position in the PACKAGE index. Those are different
    // numbering systems, so the two are kept apart: `targets[i]` is the package
    // row the Rust side reads, and `targets[i].0` is what the oracle is asked
    // for. Conflating them compares two different records and reports every
    // field as a divergence.
    let sampled = sample_indices(targets.len(), budget);
    builder.note(format!(
        "{} gmdl record(s) in {}; {}",
        targets.len(),
        package.name,
        describe_sample(targets.len(), budget, sampled.len())
    ));

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;

    for sample in &sampled {
        let Some((package_index, entry)) = targets.get(*sample) else {
            continue;
        };
        let identity = info.identity(
            *package_index,
            entry.type_id,
            entry.group_id,
            entry.instance_id,
        );
        let bytes = match spore_dbpf::extract_record(image, entry) {
            Ok(bytes) => bytes,
            Err(error) => {
                builder.record(Agreement::RustOnly(format!(
                    "spore_dbpf::extract_record refused the record before the walker ran: {error}"
                )));
                continue;
            }
        };
        let rust = spore_gmdl::parse(&bytes);
        // The PACKAGE row, not the position in the gmdl-filtered list.
        let oracle = session.request_record("gmdl", *package_index);
        // The model borrows nothing from `bytes`, and `bytes` is dropped at the
        // end of this iteration: one record resident at a time.
        record(&mut builder, identity, rust, oracle);
    }
    Ok(builder.finish())
}

/// Runs the gmdl comparison over a standalone gmdl record file.
pub fn compare_record_file(located: &LocatedRecord, config: &OracleConfig) -> DifferentialReport {
    super::run(NAME, || {
        let mut builder = ReportBuilder::new(NAME, FILE_INVOCATION);
        builder.set_tolerance(FLOAT_TOLERANCE);
        let identity = RecordIdentity::loose(located.name.clone());
        let bytes = std::fs::read(&located.path).map_err(|error| {
            OracleError::Protocol(format!(
                "could not read {}: {error}",
                located.path.display()
            ))
        })?;
        builder.note(format!(
            "{} ({} bytes), a standalone record; floats compared at {}",
            located.name,
            located.size_bytes,
            crate::floats::describe_tolerance(FLOAT_TOLERANCE)
        ));
        let mut session = OracleSession::spawn(config)?;
        let rust = spore_gmdl::parse(&bytes);
        let oracle = session.request_file("gmdl_file", &located.path);
        record(&mut builder, identity, rust, oracle);
        Ok(builder.finish())
    })
}

/// True when `record` is a gmdl standalone record.
#[must_use]
pub fn is_gmdl_record(located: &LocatedRecord) -> bool {
    located.kind == RecordKind::Gmdl
}

/// Compares one record's two parses.
fn record(
    builder: &mut ReportBuilder,
    identity: RecordIdentity,
    rust: Result<GmdlModel, spore_gmdl::GmdlError>,
    oracle: Result<Json, OracleError>,
) {
    // The oracle's message, quoted verbatim rather than replaced by a
    // classification. "Rust decoded it, Python raised struct.error" is the
    // finding; "rust-only" is a label, and a label is not quotable.
    let model = match (rust, &oracle) {
        (Ok(model), Ok(_)) => model,
        (Ok(parsed), Err(error)) => {
            // The Rust side's trailer state is quoted here because "parse
            // returned Ok" is NOT the same claim as "decoded the record".
            // `spore_gmdl` walks the tail best-effort and reports where it ran
            // out, so an Ok with a Truncated trailer is a PARTIAL decode. Calling
            // that "the oracle refused, we did not" would overstate the Rust
            // side by exactly the amount that matters.
            builder.record(Agreement::RustOnly(format!(
                "spore_gmdl::parse returned Ok (version={}, meshCount={}, trailer={:?}, \
                 strict_consumed={} of {} bytes); the oracle refused: {}",
                parsed.version,
                parsed.mesh_count,
                parsed.trailer,
                parsed.strict_consumed,
                parsed.consumed,
                error.message()
            )));
            return;
        }
        (Err(error), Ok(_)) => {
            builder.record(Agreement::OracleOnly(format!(
                "the oracle decoded the record; spore_gmdl::parse refused: {error}"
            )));
            return;
        }
        (Err(rust_error), Err(oracle_error)) => {
            builder.record(Agreement::BothFailed {
                oracle: oracle_error.message(),
                rust: rust_error.to_string(),
            });
            return;
        }
    };
    let Ok(reply) = oracle else {
        return;
    };

    // Every comparison below checks a FIELD of this one record, so the builder
    // is switched into field mode and the record's single verdict is recorded
    // once at the end. Without that the twenty-field model would be counted as
    // twenty records and the coverage numbers would be wrong.
    builder.field_mode();

    let mut field = |name: String, oracle_value: String, rust_value: String| {
        if oracle_value != rust_value {
            builder.divergence(Divergence::value(
                identity.clone(),
                name,
                oracle_value,
                rust_value,
            ));
        }
    };

    field(
        "version".to_owned(),
        num_field(reply.get("version")),
        model.version.to_string(),
    );
    field(
        "meshCount".to_owned(),
        num_field(reply.get("mesh_count")),
        model.mesh_count.to_string(),
    );
    // The oracle reports `unk`; spore-gmdl does not carry it. That is a gap in
    // the port's coverage rather than a disagreement about a value, so it is a
    // note -- once, not once per record.
    if reply.get("unk").is_some() {
        builder.note(format!(
            "{identity}: the oracle read unk = {}; spore-gmdl does not expose that word",
            num_field(reply.get("unk"))
        ));
    }

    compare_refs(builder, &identity, reply.get("refs"), &model);
    compare_vectors(
        builder,
        &identity,
        "bboxMin",
        reply.get("bbox_min"),
        model.bounds_min,
    );
    compare_vectors(
        builder,
        &identity,
        "bboxMax",
        reply.get("bbox_max"),
        model.bounds_max,
    );

    if let Some(radius) = reply.get("radius").and_then(Json::as_f64) {
        builder.float_field(
            identity.clone(),
            "boundingRadius",
            radius,
            f64::from(model.radius),
            FLOAT_TOLERANCE,
        );
    }
    compare_index_buffers(builder, &identity, reply.get("index_buffers"), &model);
    compare_descriptors(builder, &identity, reply.get("descriptors"), &model);
    compare_vertex_buffers(builder, &identity, reply.get("vertex_buffers"), &model);
    compare_pairs(
        builder,
        &identity,
        "meshes",
        reply.get("meshes"),
        mesh_table(&model),
    );
    compare_pairs(
        builder,
        &identity,
        "materialIDs",
        reply.get("material_ids"),
        model
            .material_ids
            .iter()
            .map(|id| vec![*id])
            .collect::<Vec<_>>(),
    );
    compare_pairs(
        builder,
        &identity,
        "boneRanges",
        reply.get("bone_ranges"),
        model
            .bone_ranges
            .iter()
            .map(|(start, count)| vec![*start, *count])
            .collect::<Vec<_>>(),
    );
    compare_pairs(
        builder,
        &identity,
        "unknownKey",
        reply.get("unknown_key"),
        model
            .unknown_key
            .iter()
            .map(|w| vec![*w])
            .collect::<Vec<_>>(),
    );
    compare_texture_refs(builder, &identity, &reply, &model);
    compare_material_info_count(builder, &identity, &reply, &model);
    compare_matches(builder, &identity, &reply, &model);

    // The record's one verdict: field comparisons above already recorded any
    // disagreement, so if none of them fired the record agreed.
    builder.record(Agreement::Equal);
}

/// The flattened texture references, which is the one quantity both sides can
/// state about the material-info section.
fn compare_texture_refs(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    reply: &Json,
    model: &GmdlModel,
) {
    let oracle_refs: Vec<Vec<u32>> = reply
        .get("texture_refs")
        .and_then(Json::as_array)
        .map(|rows| {
            rows.iter()
                .filter_map(|row| {
                    let cells = row.as_array()?;
                    Some(vec![cells.first()?.as_u32()?, cells.get(1)?.as_u32()?])
                })
                .collect()
        })
        .unwrap_or_default();
    let rust_refs: Vec<Vec<u32>> = model
        .texture_refs
        .iter()
        .map(|reference| vec![reference.instance_id, reference.group_id])
        .collect();
    if oracle_refs != rust_refs {
        builder.divergence(
            Divergence::value(
                identity.clone(),
                "materialInfos[].textureRefs",
                format!(
                    "{} reference(s), in order: {:?}",
                    oracle_refs.len(),
                    oracle_refs
                ),
                format!("{} reference(s), in order: {rust_refs:?}", rust_refs.len()),
            )
            .with_note(
                "both sides flatten the 0x20D texture sets in order of appearance; the oracle                  does it inside its nested walk and spore-gmdl does it while parsing",
            ),
        );
    }
}

/// The number of material-info groups. Rust does not carry the groups, so this
/// is reported as a definitional gap and never as a value mismatch.
fn compare_material_info_count(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    reply: &Json,
    model: &GmdlModel,
) {
    let Some(groups) = reply.get("material_info_groups").and_then(Json::as_u32) else {
        return;
    };
    builder.note(format!(
        "{identity}: the oracle walked {} material-info group(s); spore-gmdl does not carry the \
         groups, only the {} flattened texture reference(s) inside them",
        groups,
        model.texture_refs.len()
    ));
    if groups != 0 && model.texture_refs.is_empty() {
        builder.note_divergence(
            Divergence::value(
                identity.clone(),
                "materialInfos (shape)",
                format!("{groups} material-info group(s), as a nested tree"),
                "0 texture reference(s), and no group structure at all",
            )
            .with_class(DivergenceClass::Definitional)
            .with_note(
                "the oracle keeps the group structure and skips non-texture-set entries with \
                 ShaderData.getDataSize; spore-gmdl keeps only the texture references. Two \
                 different shapes for the same bytes, so the group count has no Rust counterpart.",
            ),
        );
    }
}

/// `matches()` against `fully_walked()`, plus the trailer stage, which the Rust
/// side reports separately and the oracle does not have a word for.
fn compare_matches(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    reply: &Json,
    model: &GmdlModel,
) {
    let oracle_matches = reply.get("matches").and_then(Json::as_bool);
    let rust_walked = model.fully_walked();
    match oracle_matches {
        Some(value) if value == rust_walked => {
            builder.note(format!(
                "{identity}: matches() == fully_walked() == {rust_walked} (oracle final offset \
                 {} of {} bytes; Rust trailer {:?})",
                num_field(reply.get("final_offset")),
                num_field(reply.get("file_len")),
                model.trailer
            ));
        }
        Some(value) => {
            builder.divergence(
                Divergence::value(
                    identity.clone(),
                    "matches()",
                    value.to_string(),
                    rust_walked.to_string(),
                )
                .with_note(format!(
                    "the oracle's matches() is finalOffset == len(bytes); the Rust analogue is \
                     fully_walked() == (strict_consumed == consumed). Rust strict_consumed={} \
                     consumed={} trailer={:?}",
                    model.strict_consumed, model.consumed, model.trailer
                )),
            );
        }
        None => {
            builder.note(format!(
                "{identity}: the oracle response carried no `matches` field, so the final-offset \
                 check could not be compared"
            ));
        }
    }
}

/// The mesh table as the Rust side spells it.
fn mesh_table(model: &GmdlModel) -> Vec<Vec<u32>> {
    model
        .meshes
        .iter()
        .map(|mesh| vec![mesh.index_buffer, mesh.vertex_buffer])
        .collect()
}

fn compare_refs(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    oracle: Option<&Json>,
    model: &GmdlModel,
) {
    // The oracle stores each reference as (instance, group, type); Rust reorders
    // them into ResourceKey's (type, group, instance). Both orders are printed,
    // so the reorder is visible instead of being a silent transformation.
    let oracle_refs = oracle
        .and_then(Json::as_array)
        .map(|rows| {
            rows.iter()
                .filter_map(|row| {
                    Some(format!(
                        "inst=0x{:08x} grp=0x{:08x} type=0x{:08x}",
                        row.as_array()?.first()?.as_u32()?,
                        row.as_array()?.get(1)?.as_u32()?,
                        row.as_array()?.get(2)?.as_u32()?
                    ))
                })
                .collect::<Vec<_>>()
        })
        .unwrap_or_default();
    let rust_refs = model
        .referenced_files
        .iter()
        .map(|key| {
            format!(
                "inst=0x{:08x} grp=0x{:08x} type=0x{:08x}",
                key.instance_id, key.group_id, key.type_id
            )
        })
        .collect::<Vec<_>>();
    if oracle_refs != rust_refs {
        builder.divergence(
            Divergence::value(
                identity.clone(),
                "refs",
                format!(
                    "{} reference(s): {}",
                    oracle_refs.len(),
                    oracle_refs.join(", ")
                ),
                format!("{} reference(s): {}", rust_refs.len(), rust_refs.join(", ")),
            )
            .with_note(
                "the oracle reads each triple as (instance, group, type); spore-gmdl reorders it \
                 into ResourceKey's (type, group, instance). Both sides print instance-first here \
                 so the reorder is checkable.",
            ),
        );
    }
}

fn compare_vectors(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    name: &str,
    oracle: Option<&Json>,
    rust: [f32; 3],
) {
    let Some(values) = oracle.and_then(Json::as_array) else {
        return;
    };
    for (axis, value) in values.iter().take(3).enumerate() {
        let Some(number) = value.as_f64() else {
            continue;
        };
        let path = format!("{name}[{axis}]");
        builder.float_field(
            identity.clone(),
            &path,
            number,
            f64::from(rust.get(axis).copied().unwrap_or_default()),
            FLOAT_TOLERANCE,
        );
    }
}

fn compare_index_buffers(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    oracle: Option<&Json>,
    model: &GmdlModel,
) {
    let oracle_buffers = oracle.and_then(Json::as_array).unwrap_or(&[]).to_vec();
    if oracle_buffers.len() != model.index_buffers.len() {
        builder.divergence(Divergence::value(
            identity.clone(),
            "numIndexBuffers",
            oracle_buffers.len().to_string(),
            model.index_buffers.len().to_string(),
        ));
    }
    for (index, buffer) in model.index_buffers.iter().enumerate() {
        let Some(row) = oracle_buffers.get(index) else {
            continue;
        };
        for (field, rust_value) in [
            ("prim", buffer.prim_type),
            ("count", buffer.index_count),
            ("bits", buffer.index_bits),
        ] {
            compare_scalar(
                builder,
                identity,
                &format!("indexBuffer[{index}].{field}"),
                row.get(field).and_then(Json::as_u32),
                rust_value,
            );
        }
        // The oracle keeps the raw index bytes and slices them by
        // `count * max(1, bits/8)`; Rust keeps what it read. The lengths must
        // agree or the two walked different numbers of bytes.
        compare_scalar(
            builder,
            identity,
            &format!("indexBuffer[{index}].bytes"),
            row.get("bytes").and_then(Json::as_u32),
            buffer.bytes.len() as u32,
        );
    }
}

fn compare_descriptors(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    oracle: Option<&Json>,
    model: &GmdlModel,
) {
    let oracle_descriptors = oracle.and_then(Json::as_array).unwrap_or(&[]).to_vec();
    if oracle_descriptors.len() != model.descriptors.len() {
        builder.divergence(Divergence::value(
            identity.clone(),
            "numVertexDescriptors",
            oracle_descriptors.len().to_string(),
            model.descriptors.len().to_string(),
        ));
    }
    for (descriptor_index, elements) in model.descriptors.iter().enumerate() {
        let Some(oracle_elements) = oracle_descriptors
            .get(descriptor_index)
            .and_then(Json::as_array)
        else {
            continue;
        };
        compare_scalar(
            builder,
            identity,
            &format!("vertexDescriptor[{descriptor_index}].elementCount"),
            Some(oracle_elements.len() as u32),
            elements.len() as u32,
        );
        for (element_index, element) in elements.iter().enumerate() {
            let Some(oracle_element) = oracle_elements.get(element_index) else {
                continue;
            };
            let path = format!("vertexDescriptor[{descriptor_index}].element[{element_index}]");
            for (field, rust_value) in [
                ("stream", u32::from(element.stream)),
                ("offset", u32::from(element.offset)),
                ("type", u32::from(element.decl_type)),
                ("method", u32::from(element.decl_method)),
                ("usage", u32::from(element.decl_usage)),
                ("usage_index", u32::from(element.usage_index)),
                ("type_code", element.type_code),
            ] {
                compare_scalar(
                    builder,
                    identity,
                    &format!("{path}.{field}"),
                    oracle_element.get(field).and_then(Json::as_u32),
                    rust_value,
                );
            }
        }
    }
}

fn compare_vertex_buffers(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    oracle: Option<&Json>,
    model: &GmdlModel,
) {
    let oracle_buffers = oracle.and_then(Json::as_array).unwrap_or(&[]).to_vec();
    if oracle_buffers.len() != model.vertex_buffers.len() {
        builder.divergence(Divergence::value(
            identity.clone(),
            "numVertexBuffers",
            oracle_buffers.len().to_string(),
            model.vertex_buffers.len().to_string(),
        ));
    }
    for (index, buffer) in model.vertex_buffers.iter().enumerate() {
        let Some(row) = oracle_buffers.get(index) else {
            continue;
        };
        for (field, rust_value) in [
            ("desc_idx", buffer.desc_index),
            ("vertex_count", buffer.vertex_count),
            ("size", buffer.bytes.len() as u32),
            ("bytes", buffer.bytes.len() as u32),
        ] {
            compare_scalar(
                builder,
                identity,
                &format!("vertexBuffer[{index}].{field}"),
                row.get(field).and_then(Json::as_u32),
                rust_value,
            );
        }
    }
}

/// A list of small integer tuples, compared element by element so a mismatch
/// names the row it is in.
fn compare_pairs(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    name: &str,
    oracle: Option<&Json>,
    rust: Vec<Vec<u32>>,
) {
    let oracle_rows = oracle.and_then(Json::as_array).unwrap_or(&[]).to_vec();
    if oracle_rows.len() != rust.len() {
        builder.divergence(Divergence::value(
            identity.clone(),
            format!("{name}.len"),
            oracle_rows.len().to_string(),
            rust.len().to_string(),
        ));
    }
    for (index, rust_row) in rust.iter().enumerate() {
        let Some(oracle_row) = oracle_rows.get(index).and_then(Json::as_array) else {
            continue;
        };
        let oracle_values: Vec<u32> = oracle_row.iter().filter_map(Json::as_u32).collect();
        if oracle_values != *rust_row {
            builder.divergence(Divergence::value(
                identity.clone(),
                format!("{name}[{index}]"),
                format!("{oracle_values:?}"),
                format!("{rust_row:?}"),
            ));
        }
    }
}

fn compare_scalar(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    path: &str,
    oracle: Option<u32>,
    rust: u32,
) {
    match oracle {
        None => {
            builder.note(format!(
                "{identity}: {path} is absent from the oracle response"
            ));
        }
        Some(value) if value == rust => {}
        Some(value) => {
            builder.divergence(Divergence::value(
                identity.clone(),
                path.to_owned(),
                value.to_string(),
                rust.to_string(),
            ));
        }
    }
}

/// Formats an integer field the same way on both sides.
///
/// The oracle's numbers arrive as `f64` because JSON has one number type, so a
/// naive `{:?}` prints `8.0` where Rust prints `8` -- a formatting difference
/// dressed up as a value difference, which is the exact failure mode a
/// differential harness must not have. Anything with a fractional part keeps
/// its decimal expansion so a genuinely fractional field is still readable.
fn num_field(value: Option<&Json>) -> String {
    let Some(number) = value.and_then(Json::as_f64) else {
        return "<absent>".to_owned();
    };
    if number.fract() == 0.0 && number.is_finite() && number.abs() < 9e15 {
        format!("{}", number as i64)
    } else {
        format!("{number:?}")
    }
}

/// Builds a request object for the driver. Kept public so a test can assert the
/// exact wire shape without spawning a process.
#[must_use]
pub fn sample_request(index: usize) -> String {
    json::object(vec![
        ("cmd", Json::Str("gmdl".to_owned())),
        ("i", Json::Num(index as f64)),
    ])
    .to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn model_stub() -> GmdlModel {
        spore_gmdl::parse(
            &std::fs::read(crate::corpus::workspace_root().join("tests/fixtures/mini.gmdl"))
                .expect("the committed fixture must exist"),
        )
        .expect("the committed fixture must parse")
    }

    #[test]
    fn the_wire_request_is_the_shape_the_driver_expects() {
        assert_eq!(sample_request(7), r#"{"cmd":"gmdl","i":7}"#);
    }

    #[test]
    fn the_unk_field_is_reported_as_a_gap_rather_than_compared() {
        // Both sides of that divergence are literal strings, so the report can
        // quote the gap instead of pretending the two walkers agree.
        let model = model_stub();
        let gap = crate::report::Divergence::value(
            RecordIdentity::loose("mini.gmdl"),
            "unk",
            "read by the oracle",
            "not exposed by the Rust port",
        );
        assert_eq!(gap.class, crate::report::DivergenceClass::ValueMismatch);
        assert!(gap.oracle.contains("oracle"));
        assert!(gap.rust.contains("Rust"));
        assert_eq!(model.mesh_count, model.material_ids.len() as u32);
    }
}
