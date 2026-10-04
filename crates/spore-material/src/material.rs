//! The material side: what a gmdl material id means, and the texture bindings
//! that can honestly be attached to it.
//!
//! # The two non-findings this module is built around
//!
//! 1. **A material id has no known meaning.** The gmdl record carries one 32-bit
//!    id per mesh (`0x407DFDDB` on the documented asset) and nothing in the
//!    record says what it names. The C++ reference, `src/assets/MaterialRegistry.cpp`,
//!    keeps a registry *the engine populates from outside* — which is the
//!    strongest available evidence that the mapping is not in the game data at
//!    all. So [`MaterialModel::name`] is always `None` and the id's meaning is
//!    recorded as `Fact::unavailable("no_material_registry")`: a non-finding, not
//!    a default colour and not a name derived from the bits.
//!
//! 2. **A sampler role is unknown.** A gmdl texture-set entry (`0x20D`) is 16
//!    skipped bytes followed by `{instance, group}`. `spore-gmdl` steps over
//!    those 16 bytes without reading them, so nothing downstream can say whether
//!    a texture is a diffuse map, a specular map, a normal map or a mask.
//!    [`SamplerRole`] therefore has exactly one variant, [`SamplerRole::Unresolved`],
//!    and the fact is recorded per binding.
//!
//! # Which textures belong to a material
//!
//! **They are not known, and this module does not pretend otherwise.** The gmdl
//! walk reads a table of per-material blocks, each holding a texture set, and
//! flattens every reference into one list without recording which block it came
//! from. So [`MaterialModel::bindings`] holds the **whole model's** texture set
//! and [`MaterialModel::binding_scope`] says so in the type, with
//! [`claims::MATERIAL_TEXTURE_OWNERSHIP`] recording the non-finding. Attributing
//! textures to materials is a real gap in the gmdl walk, not a rounding
//! decision this crate gets to make.

use spore_core::evidence::Fact;
use spore_core::ResourceKey;
use spore_gmdl::{GmdlModel, GmdlTextureRef};

use crate::claims;

/// One graded statement about a material or a texture.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct MaterialClaim {
    /// The stable subject string; see the [`claims`] module for the full list.
    pub subject: String,
    /// The statement, with its grade and provenance — or a non-finding.
    pub fact: Fact<&'static str>,
}

impl MaterialClaim {
    /// Builds a claim from one of the crate's declared subjects.
    pub fn new(subject: &'static str, fact: Fact<&'static str>) -> Self {
        Self {
            subject: subject.to_owned(),
            fact,
        }
    }

    /// Looks a claim up by subject.
    pub fn claim<'a>(claims: &'a [MaterialClaim], subject: &str) -> Option<&'a MaterialClaim> {
        claims.iter().find(|entry| entry.subject == subject)
    }
}

/// Which sampler stage a texture binding feeds.
///
/// The enum has exactly one variant because the format has not been decoded
/// far enough to justify a second. Adding `Diffuse` would mean decoding the 16
/// skipped bytes of a texture-set entry and proving what the sampler word means
/// in the shader that consumes it — neither of which this build has done.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum SamplerRole {
    /// The binding's role is not known. Always, in this build.
    Unresolved,
}

/// One texture reference bound to a material, with its role left open.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct TextureBinding {
    /// What this texture feeds. Always [`SamplerRole::Unresolved`].
    pub role: SamplerRole,
    /// The reference exactly as the gmdl record carried it.
    pub reference: GmdlTextureRef,
}

impl TextureBinding {
    /// The identity this binding would resolve to under `assumed_type`.
    ///
    /// The type word is a parameter and not part of the binding, because the
    /// record does not carry one; see [`claims::TEXTURE_REFERENCE_TYPE_WORD`].
    pub fn key(&self, assumed_type: u32) -> ResourceKey {
        ResourceKey::new(
            assumed_type,
            self.reference.group_id,
            self.reference.instance_id,
        )
    }
}

/// How much of the model's texture set a [`MaterialModel`]'s bindings cover.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum BindingScope {
    /// Every texture reference in the model, because the gmdl walk does not
    /// record which texture-set block belonged to which material id.
    ///
    /// The only variant, and it is the only honest one available today.
    WholeModel,
}

impl BindingScope {
    /// The canonical spelling, for logs and JSON.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::WholeModel => "whole-model",
        }
    }
}

/// One material as far as this build can honestly describe it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct MaterialModel {
    /// The opaque 32-bit id, carried verbatim from the gmdl record. One per
    /// mesh, in record order.
    pub material_id: u32,
    /// A name for [`Self::material_id`], when this build has one. Always `None`
    /// here: see [`claims::MATERIAL_NAME`] and [`material_name`].
    pub name: Option<&'static str>,
    /// The texture references associated with this material — which, in this
    /// build, means the whole model's. Read [`Self::binding_scope`].
    pub bindings: Vec<TextureBinding>,
    /// Every graded statement this crate makes about this material, including
    /// the two non-findings.
    pub claims: Vec<MaterialClaim>,
    /// The extent of [`Self::bindings`], stated in the type rather than only in a
    /// comment.
    pub binding_scope: BindingScope,
}

impl MaterialModel {
    /// Looks a claim up by subject.
    pub fn claim(&self, subject: &str) -> Option<&MaterialClaim> {
        MaterialClaim::claim(&self.claims, subject)
    }

    /// The claims that are non-findings, i.e. the things this build does not
    /// know.
    ///
    /// A renderer that wants a "what is missing here" summary reads this rather
    /// than scanning for absence itself.
    pub fn unknowns(&self) -> impl Iterator<Item = &MaterialClaim> {
        self.claims
            .iter()
            .filter(|claim| claim.fact.is_unavailable())
    }
}

/// The name of a material id, which this build does not have.
///
/// Returns `None` for **every** id, including `0x407DFDDB`. This function exists
/// so that the "no registry" fact is a single greppable statement instead of an
/// assumption spread through the code, and so that the field
/// [`MaterialModel::name`] has exactly one place it is filled from.
pub fn material_name(_material_id: u32) -> Option<&'static str> {
    // A registry would be a lookup keyed on the id. The reference implementation
    // has one and the engine populates it from outside, which means the mapping
    // is not carried by the records this crate can read. Deriving a name from
    // the bits would be a fabrication presented as a fact.
    None
}

/// The observed layout of one gmdl texture-set entry.
const TEXTURE_SET_ENTRY_LAYOUT_TEXT: &str =
    "A 0x20D entry is 16 skipped bytes followed by the referenced record's instance and \
     group ids. The 16 bytes are not decoded by spore-gmdl, so no sampler stage, layer or \
     flag can be read from them.";

/// The observation text for a material id that was read and not interpreted.
const MATERIAL_ID_OBSERVED_TEXT: &str =
    "The id is read verbatim from the gmdl mesh table, one word per mesh, and nothing in \
     the record or in any record this build can read interprets it.";

/// The observation text for a model that referenced no textures at all.
const NO_BINDINGS_TEXT: &str = "this model referenced no textures";

/// The observation text for a model whose whole texture set is bound.
const WHOLE_MODEL_BINDINGS_TEXT: &str =
    "this model's whole texture set, once per binding; the gmdl walk does not record which \
     texture-set block a reference came from";

/// Builds the claim set every material carries.
///
/// `binding_count` is this model's whole texture-set length, which is what the
/// bindings cover (see [`BindingScope`]).
fn material_claims(binding_count: usize) -> Vec<MaterialClaim> {
    vec![
        MaterialClaim::new(
            claims::MATERIAL_NAME,
            claims::non_finding(claims::MATERIAL_NAME),
        ),
        MaterialClaim::new(
            claims::MATERIAL_ID_MEANING,
            claims::non_finding(claims::MATERIAL_ID_MEANING),
        ),
        MaterialClaim::new(
            claims::SAMPLER_ROLE,
            claims::non_finding(claims::SAMPLER_ROLE),
        ),
        MaterialClaim::new(
            claims::MATERIAL_TEXTURE_OWNERSHIP,
            claims::non_finding(claims::MATERIAL_TEXTURE_OWNERSHIP),
        ),
        MaterialClaim::new(
            claims::TEXTURE_SET_ENTRY_LAYOUT,
            claims::graded(
                claims::TEXTURE_SET_ENTRY_LAYOUT,
                claims::PROV_GMDL_WALK,
                TEXTURE_SET_ENTRY_LAYOUT_TEXT,
            ),
        ),
        MaterialClaim::new(
            claims::MATERIAL_ID_READ_VERBATIM,
            claims::graded(
                claims::MATERIAL_ID_READ_VERBATIM,
                claims::PROV_GMDL_WALK,
                MATERIAL_ID_OBSERVED_TEXT,
            ),
        ),
        MaterialClaim::new(
            claims::MATERIAL_BINDING_COUNT,
            claims::graded(
                claims::MATERIAL_BINDING_COUNT,
                claims::PROV_RESOLVE,
                if binding_count == 0 {
                    NO_BINDINGS_TEXT
                } else {
                    WHOLE_MODEL_BINDINGS_TEXT
                },
            ),
        ),
    ]
}

/// One [`MaterialModel`] per material id in `model`, in record order.
///
/// The result is empty when the model declared no material ids, which is the
/// shape of the real record captured in
/// `tests/expected/real_gmdl_1006.json` (`meshCount` 0). That is an absence of
/// materials in the record, not an error.
pub fn model_materials(model: &GmdlModel) -> Vec<MaterialModel> {
    let bindings: Vec<TextureBinding> = model
        .texture_refs
        .iter()
        .map(|reference| TextureBinding {
            role: SamplerRole::Unresolved,
            reference: *reference,
        })
        .collect();

    model
        .material_ids
        .iter()
        .map(|material_id| MaterialModel {
            material_id: *material_id,
            name: material_name(*material_id),
            bindings: bindings.clone(),
            claims: material_claims(bindings.len()),
            binding_scope: BindingScope::WholeModel,
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    use spore_core::evidence::{EvidenceLevel, EvidenceState};

    /// The documented asset's material id, measured with `osptool` on
    /// `SPORE/Data/Spore_Content.package` (2026-10-04).
    const REAL_MATERIAL_ID: u32 = 0x407D_FDDB;

    #[test]
    fn no_material_id_ever_gets_a_name() {
        for id in [REAL_MATERIAL_ID, 0, 1, u32::MAX, 0x1234_5678] {
            assert_eq!(material_name(id), None, "id 0x{id:08x} must stay unnamed");
        }
    }

    #[test]
    fn sampler_role_has_exactly_one_variant() {
        // Not a style preference: a second variant would be a claim with no
        // evidence behind it. Match exhaustively so adding one breaks here.
        let role = SamplerRole::Unresolved;
        assert_eq!(role, SamplerRole::Unresolved);
        assert_eq!(BindingScope::WholeModel.as_str(), "whole-model");
    }

    #[test]
    fn a_binding_key_is_the_reference_plus_the_caller_assumed_type() {
        let binding = TextureBinding {
            role: SamplerRole::Unresolved,
            reference: GmdlTextureRef {
                instance_id: 0x067A_07F0,
                group_id: 0x4063_2900,
            },
        };
        assert_eq!(
            binding.key(spore_texture::RASTER_TYPE),
            ResourceKey::new(spore_texture::RASTER_TYPE, 0x4063_2900, 0x067A_07F0)
        );
    }

    #[test]
    fn the_material_claims_are_four_non_findings_and_graded_observations() {
        let claims = material_claims(3);
        for subject in [
            claims::MATERIAL_NAME,
            claims::MATERIAL_ID_MEANING,
            claims::SAMPLER_ROLE,
            claims::MATERIAL_TEXTURE_OWNERSHIP,
        ] {
            let claim = MaterialClaim::claim(&claims, subject).expect(subject);
            assert!(claim.fact.is_unavailable(), "{subject}");
            assert_eq!(claim.fact.level(), EvidenceLevel::Unknown, "{subject}");
            assert_eq!(
                claim.fact.evidence_state(),
                EvidenceState::Missing,
                "{subject}"
            );
            assert!(claim.fact.provenance().is_empty(), "{subject}");
            assert!(claim.fact.value().is_none(), "{subject}");
        }
        for subject in [
            claims::TEXTURE_SET_ENTRY_LAYOUT,
            claims::MATERIAL_ID_READ_VERBATIM,
            claims::MATERIAL_BINDING_COUNT,
        ] {
            let claim = MaterialClaim::claim(&claims, subject).expect(subject);
            assert!(claim.fact.is_available(), "{subject}");
            assert_ne!(claim.fact.level(), EvidenceLevel::Unknown, "{subject}");
            assert!(!claim.fact.provenance().is_empty(), "{subject}");
        }
    }

    #[test]
    fn binding_count_is_stated_not_silently_zero() {
        let empty = material_claims(0);
        let claim = MaterialClaim::claim(&empty, claims::MATERIAL_BINDING_COUNT).unwrap();
        assert_eq!(
            claim.fact.value(),
            Some(&NO_BINDINGS_TEXT),
            "no bindings is a statement, not an absent one"
        );
        let some = material_claims(3);
        let claim = MaterialClaim::claim(&some, claims::MATERIAL_BINDING_COUNT).unwrap();
        assert_eq!(claim.fact.value(), Some(&WHOLE_MODEL_BINDINGS_TEXT));
    }
}
