//! The cross-record reference layer: which record points at which, and does it
//! resolve.
//!
//! # Twenty-six typed reference fields
//!
//! [`CellReferenceField`] enumerates them. They are **typed**, not a bag of
//! `u32`s, because the type of the target is part of the claim: `cell.loot`
//! names a `0xD92AF091` loot table and resolves; `cell.leak` stores an instance
//! id with **no type word at all** and cannot be looked up by anybody.
//! [`CellContentRecord::references`] is the single authority on which fields
//! emit a reference, and [`CellReferenceResolver::resolve`] refuses any
//! `(field, index, instance)` triple the record does not actually produce.
//!
//! # Three states of a reference, not two
//!
//! | state | meaning | reported as |
//! |---|---|---|
//! | resolved | a catalogue record has that `(type, instance)` | the record |
//! | unresolved | the field says what it wants and the catalogue lacks it | [`CellReferenceError::NotFound`] |
//! | **non-finding** | the field does not say what it wants | [`CellReferenceError::UnknownTypeWord`] / [`CellReferenceError::OutsideFamily`] |
//!
//! The third row is the one that is easy to lose. Ten of the twenty-six fields
//! carry no type word, and one (`world.advect.advectID`) names a record type from
//! another subsystem. Collapsing either into "not found" would assert that a
//! search happened and came up empty. [`CellReferenceError::is_non_finding`]
//! separates them so a caller can report *coverage* honestly.
//!
//! # Groups are genuinely unknown
//!
//! A reference stores an **instance id only**. `cell.structure` says "some
//! `0x4B9EF6DC` whose instance is `0x…`" and nothing about its group. When two
//! catalogue rows share that `(type, instance)` pair the reference is
//! [`CellReferenceError::Ambiguous`] rather than resolved to whichever row
//! happened to be first.

use core::fmt;
use std::collections::BTreeMap;
use std::collections::BTreeSet;

use spore_core::{ResourceKey, WILDCARD};

use crate::error::CellReferenceError;

/// The twenty-six fields of this record family that hold a reference.
///
/// `CellReferenceField::NONE` exists as a "no field" sentinel for
/// [`CellReference::field`]'s initial state and is not one of the twenty-six.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum CellReferenceField {
    /// No field. Only ever the initial value of a hand-built reference.
    NONE,
    /// A `globals` world slot (`world_1`..`world_5`,
    /// `worldBackground_1`..`worldBackground_5`, `worldRandom`,
    /// `worldRandomBg`): twelve slots, all naming a `0x9B8E862F`.
    GlobalsWorld,
    /// `globals.effectMapEntry`: a `0x433FB70C`.
    GlobalsEffectMap,
    /// `globals.backgroundMapEntry`: a `0x612B3191`.
    GlobalsBackgroundMap,
    /// The two `globals` *start-cell* slots: `startCell` (index 0, names a
    /// `0xDFAD9F51`) and `startingCellKey` (index 1, **no type word** — the
    /// corpus value names a `prop`). One field, two slots, two different
    /// answers, and the field count stays at 26. What each slot declares lives
    /// on [`CellReference::declares_type`], not here. See
    /// [`crate::globals::GLOBALS_REFERENCE_FIELDS`].
    GlobalsCell,
    /// `globals.keyLookAlgorithm`: a `0xDBA35AE2`.
    GlobalsLookAlgorithm,
    /// `cell.structure`: a `0x4B9EF6DC`.
    CellStructure,
    /// `cell.break`: an instance id with **no type word**.
    CellBreak,
    /// `cell.pieces`: an instance id with **no type word**.
    CellPieces,
    /// `cell.leak`: an instance id with **no type word**.
    CellLeak,
    /// `cell.expel`: an instance id with **no type word**.
    CellExpel,
    /// `cell.explosionTable`: an instance id with **no type word**.
    CellExplosionTable,
    /// `cell.loot`: a `0xD92AF091`.
    CellLoot,
    /// `cell.poison`: an instance id with **no type word**.
    CellPoison,
    /// `cell.ai{,.hard,.easy}.spawnOutput`: no type word.
    CellAiSpawnOutput,
    /// `cell.ai{,.hard,.easy}.digestionOutput`: no type word.
    CellAiDigestionOutput,
    /// `world.populate[i].populate`: a `0xDA141C1B`.
    WorldPopulate,
    /// `world.advect[i].advectID`: a `0x04805684` flow field, outside this family.
    WorldAdvect,
    /// `populate.markers[i].distributeCell`: a `0xDFAD9F51`.
    PopulateDistributeCell,
    /// `populate.markers[i].clusterCell`: a `0xDFAD9F51`.
    PopulateClusterCell,
    /// `lookAlgorithm.entries[i].{player,npc,epic}`: a `0x8C042499`.
    LookTable,
    /// `lootTable.entries[i].cell`: a `0xDFAD9F51`.
    LootCell,
    /// `lootTable.entries[i].table`: a `0xD92AF091`.
    LootTable,
    /// `structure.{onDeath,onDeathSmall,onDeathLarge,onHatch,onStartHatch}`: no
    /// type word, indexed 0..4 in that order.
    StructureHeaderEffect,
    /// `structure.attachments[i].structure`: a `0x4B9EF6DC`.
    StructureAttachmentStructure,
    /// `structure.attachments[i].randomCreature`: a `0xF9C3D770`.
    StructureAttachmentRandomCreature,
    /// `structure.attachments[i].effectID`: no type word.
    StructureAttachmentEffect,
}

impl CellReferenceField {
    /// Every reference field, in declaration order. 26 entries.
    pub const ALL: [Self; 26] = [
        Self::GlobalsWorld,
        Self::GlobalsEffectMap,
        Self::GlobalsBackgroundMap,
        Self::GlobalsCell,
        Self::GlobalsLookAlgorithm,
        Self::CellStructure,
        Self::CellBreak,
        Self::CellPieces,
        Self::CellLeak,
        Self::CellExpel,
        Self::CellExplosionTable,
        Self::CellLoot,
        Self::CellPoison,
        Self::CellAiSpawnOutput,
        Self::CellAiDigestionOutput,
        Self::WorldPopulate,
        Self::WorldAdvect,
        Self::PopulateDistributeCell,
        Self::PopulateClusterCell,
        Self::LookTable,
        Self::LootCell,
        Self::LootTable,
        Self::StructureHeaderEffect,
        Self::StructureAttachmentStructure,
        Self::StructureAttachmentRandomCreature,
        Self::StructureAttachmentEffect,
    ];

    /// The canonical spelling, used in error messages and dumps.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::NONE => "none",
            Self::GlobalsWorld => "globals.world",
            Self::GlobalsEffectMap => "globals.effectMapEntry",
            Self::GlobalsBackgroundMap => "globals.backgroundMapEntry",
            // Both start-cell slots share this field and are told apart by index,
            // so the spelling names both.
            Self::GlobalsCell => "globals.startCell/startingCellKey",
            Self::GlobalsLookAlgorithm => "globals.keyLookAlgorithm",
            Self::CellStructure => "cell.structure",
            Self::CellBreak => "cell.break",
            Self::CellPieces => "cell.pieces",
            Self::CellLeak => "cell.leak",
            Self::CellExpel => "cell.expel",
            Self::CellExplosionTable => "cell.explosionTable",
            Self::CellLoot => "cell.loot",
            Self::CellPoison => "cell.poison",
            Self::CellAiSpawnOutput => "cell.ai.spawnOutput",
            Self::CellAiDigestionOutput => "cell.ai.digestionOutput",
            Self::WorldPopulate => "world.populate.populate",
            Self::WorldAdvect => "world.advect.advectID",
            Self::PopulateDistributeCell => "populate.marker.distributeCell",
            Self::PopulateClusterCell => "populate.marker.clusterCell",
            Self::LookTable => "lookAlgorithm.lookTable",
            Self::LootCell => "lootTable.entry.cell",
            Self::LootTable => "lootTable.entry.table",
            Self::StructureHeaderEffect => "structure.header.effect",
            Self::StructureAttachmentStructure => "structure.attachment.structure",
            Self::StructureAttachmentRandomCreature => "structure.attachment.randomCreature",
            Self::StructureAttachmentEffect => "structure.attachment.effectID",
        }
    }

    /// Whether **every** slot of this field names a record type.
    ///
    /// `false` for the ten fields that store a bare instance id. One field is a
    /// *mixed* case: [`Self::GlobalsCell`] covers two slots of which only
    /// `startCell` declares the cell type, so this returns `true` for the field
    /// and the per-slot truth is on [`CellReference::declares_type`]. That is why
    /// the resolver and the checkers read the target from the reference and never
    /// from the field.
    pub const fn declares_type(self) -> bool {
        !matches!(
            self,
            Self::CellBreak
                | Self::CellPieces
                | Self::CellLeak
                | Self::CellExpel
                | Self::CellExplosionTable
                | Self::CellPoison
                | Self::CellAiSpawnOutput
                | Self::CellAiDigestionOutput
                | Self::StructureHeaderEffect
                | Self::StructureAttachmentEffect
        )
    }
}

impl fmt::Display for CellReferenceField {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// What a reference points at.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum ReferenceTarget {
    /// A record type inside this family.
    Typed(u32),
    /// The field stores an instance id and **no type word**, so it names no
    /// record type. Reproduces the C++ reference's
    /// `ResourceKey::kWildcard` type word, which is an explicit statement that
    /// the record does not say what it points at.
    Untyped,
    /// A record type that exists but is outside this family — today only
    /// `world.advect.advectID`'s `0x04805684`.
    Foreign(u32),
}

impl ReferenceTarget {
    /// The type word, or [`WILDCARD`] when the field declares none.
    pub const fn type_id(self) -> u32 {
        match self {
            Self::Typed(id) | Self::Foreign(id) => id,
            Self::Untyped => WILDCARD,
        }
    }
}

/// One reference emitted by a record.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct CellReference {
    /// The identity of the record holding the reference.
    pub source: ResourceKey,
    /// What it points at.
    pub target: ReferenceTarget,
    /// The stored instance id.
    pub instance: u32,
    /// Which field emitted it.
    pub field: CellReferenceField,
    /// The entry index. For `lookAlgorithm` the three look-table refs of entry
    /// `i` are indexed `3 * i`, `3 * i + 1`, `3 * i + 2` — player, npc, epic — so
    /// the index identifies the field inside the record and not just the row.
    pub index: usize,
}

impl CellReference {
    /// Whether **this** reference declares a type word.
    ///
    /// The authoritative version of [`CellReferenceField::declares_type`], which
    /// can only speak for a field as a whole.
    pub const fn declares_type(&self) -> bool {
        !matches!(self.target, ReferenceTarget::Untyped)
    }

    /// The target identity, or `None` when the field declares no type word.
    pub const fn target_key(&self) -> Option<ResourceKey> {
        match self.target {
            ReferenceTarget::Untyped => None,
            ReferenceTarget::Typed(id) | ReferenceTarget::Foreign(id) => {
                Some(ResourceKey::new(id, WILDCARD, self.instance))
            }
        }
    }
}

/// A decoded cell-content record: its identity and its value.
#[derive(Debug, Clone, PartialEq)]
pub struct CellContentRecord {
    /// The record's `(type, group, instance)` identity.
    pub key: ResourceKey,
    /// The decoded record.
    pub value: crate::CellContent,
}

impl CellContentRecord {
    /// Pairs the identity with a decoded value.
    pub const fn new(key: ResourceKey, value: crate::CellContent) -> Self {
        Self { key, value }
    }

    /// The record's type word.
    pub const fn type_id(&self) -> u32 {
        self.value.type_id()
    }

    /// Every reference this record emits, in a deterministic order.
    ///
    /// A field holding zero emits **nothing**. That is not the same as emitting
    /// a reference to instance 0, and the difference is preserved: `0` means
    /// "no target", and a catalogue lookup for instance 0 would be looking for
    /// a record that does not exist.
    ///
    /// `CellRandomCreatureEntry::creature_id` is deliberately **absent**: it is a
    /// soft id with no type word and no registry, and enumerating it as a
    /// reference would be the fabrication this crate exists to avoid.
    pub fn references(&self) -> Vec<CellReference> {
        use crate::CellContent as C;
        let source = self.key;
        let mut out = Vec::new();
        let mut push =
            |field: CellReferenceField, index: usize, target: ReferenceTarget, instance: u32| {
                if instance != 0 {
                    out.push(CellReference {
                        source,
                        target,
                        instance,
                        field,
                        index,
                    });
                }
            };

        match &self.value {
            C::Globals(globals) => {
                for (name, value) in globals.reference_slots() {
                    let Some(slot) = globals_slot(name) else {
                        continue;
                    };
                    push(slot.field, slot.index, slot.target, value);
                }
            }
            C::Cell(cell) => {
                push(
                    CellReferenceField::CellStructure,
                    0,
                    ReferenceTarget::Typed(crate::structure::STRUCTURE_TYPE),
                    cell.structure,
                );
                for (field, value) in [
                    (CellReferenceField::CellBreak, cell.break_),
                    (CellReferenceField::CellPieces, cell.pieces),
                    (CellReferenceField::CellLeak, cell.leak),
                    (CellReferenceField::CellExpel, cell.expel),
                    (CellReferenceField::CellExplosionTable, cell.explosion_table),
                    (CellReferenceField::CellLoot, cell.loot),
                    (CellReferenceField::CellPoison, cell.poison),
                ] {
                    let target = if field == CellReferenceField::CellLoot {
                        ReferenceTarget::Typed(crate::loot::LOOT_TABLE_TYPE)
                    } else {
                        ReferenceTarget::Untyped
                    };
                    push(field, 0, target, value);
                }
                for (index, ai) in cell.ai_tiers().iter().enumerate() {
                    push(
                        CellReferenceField::CellAiSpawnOutput,
                        index,
                        ReferenceTarget::Untyped,
                        ai.spawn_output,
                    );
                    push(
                        CellReferenceField::CellAiDigestionOutput,
                        index,
                        ReferenceTarget::Untyped,
                        ai.digestion_output,
                    );
                }
            }
            C::World(world) => {
                for (index, entry) in world.populate.iter().enumerate() {
                    push(
                        CellReferenceField::WorldPopulate,
                        index,
                        ReferenceTarget::Typed(crate::populate::POPULATE_TYPE),
                        entry.populate,
                    );
                }
                for (index, entry) in world.advect.iter().enumerate() {
                    push(
                        CellReferenceField::WorldAdvect,
                        index,
                        ReferenceTarget::Foreign(crate::world::ADVERT_FLOW_FIELD_TYPE),
                        entry.advect_id,
                    );
                }
            }
            C::Populate(populate) => {
                for (index, marker) in populate.markers.iter().enumerate() {
                    push(
                        CellReferenceField::PopulateDistributeCell,
                        index,
                        ReferenceTarget::Typed(crate::cell::CELL_TYPE),
                        marker.distribute_cell,
                    );
                    push(
                        CellReferenceField::PopulateClusterCell,
                        index,
                        ReferenceTarget::Typed(crate::cell::CELL_TYPE),
                        marker.cluster_cell,
                    );
                }
            }
            C::LookAlgorithm(algorithm) => {
                for (index, entry) in algorithm.entries.iter().enumerate() {
                    for (slot, value) in entry.look_tables().iter().enumerate() {
                        push(
                            CellReferenceField::LookTable,
                            index * 3 + slot,
                            ReferenceTarget::Typed(crate::look::LOOK_TABLE_TYPE),
                            *value,
                        );
                    }
                }
            }
            C::LootTable(table) => {
                for (index, entry) in table.entries.iter().enumerate() {
                    push(
                        CellReferenceField::LootCell,
                        index,
                        ReferenceTarget::Typed(crate::cell::CELL_TYPE),
                        entry.cell,
                    );
                    push(
                        CellReferenceField::LootTable,
                        index,
                        ReferenceTarget::Typed(crate::loot::LOOT_TABLE_TYPE),
                        entry.table,
                    );
                }
            }
            C::Structure(structure) => {
                for (index, (_, value)) in structure.header_effects().iter().enumerate() {
                    push(
                        CellReferenceField::StructureHeaderEffect,
                        index,
                        ReferenceTarget::Untyped,
                        *value,
                    );
                }
                for (index, attachment) in structure.attachments.iter().enumerate() {
                    push(
                        CellReferenceField::StructureAttachmentStructure,
                        index,
                        ReferenceTarget::Typed(crate::structure::STRUCTURE_TYPE),
                        attachment.structure,
                    );
                    push(
                        CellReferenceField::StructureAttachmentRandomCreature,
                        index,
                        ReferenceTarget::Typed(crate::spawn::RANDOM_CREATURE_TYPE),
                        attachment.random_creature,
                    );
                    // A negative effect id is NOT a reference. The C++ reference
                    // casts it to `u32`, which turns `-1` into `0xFFFFFFFF` — the
                    // same word it uses for "unset". Carrying the signed value
                    // and refusing it here is what keeps the two apart.
                    if attachment.effect_id > 0 {
                        push(
                            CellReferenceField::StructureAttachmentEffect,
                            index,
                            ReferenceTarget::Untyped,
                            attachment.effect_id as u32,
                        );
                    }
                }
            }
            C::EffectMap(_)
            | C::BackgroundMap(_)
            | C::RandomCreature(_)
            | C::Powers(_)
            | C::LookTable(_) => {}
        }
        out
    }

    /// The graded claims that apply to this record's type.
    ///
    /// `None` means *this record type does not carry that subject*, which is a
    /// third state distinct from
    /// [`spore_core::Fact::unavailable`] ("this record type carries it, and we
    /// looked and found nothing").
    pub fn claim(&self, subject: &'static str) -> Option<spore_core::Fact<&'static str>> {
        self.value.claim(subject)
    }
}

/// The `(type, instance)` identities a catalogue knows about, whether or not the
/// record itself has been decoded.
///
/// Split out from [`CellCatalogue`] for one reason: a caller that only has a list
/// of instance ids must be able to run the domain checkers **without** this crate
/// inventing placeholder records for them. `tools/spore/cellres/cellpop.py` works
/// exactly this way — it collects `cell_insts` as a `set()` and never decodes a
/// cell record — and reproducing that shape here is what keeps "we did not
/// decode this" distinguishable from "this record is empty".
#[derive(Debug, Clone, Default)]
pub struct CellInstanceIndex {
    by_type: BTreeMap<u32, BTreeSet<u32>>,
}

impl CellInstanceIndex {
    /// An empty index. Every lookup fails.
    pub fn new() -> Self {
        Self::default()
    }

    /// Records one identity.
    pub fn insert(&mut self, key: ResourceKey) {
        self.by_type
            .entry(key.type_id)
            .or_default()
            .insert(key.instance_id);
    }

    /// Builds an index from identities.
    pub fn from_keys<I: IntoIterator<Item = ResourceKey>>(keys: I) -> Self {
        let mut index = Self::new();
        for key in keys {
            index.insert(key);
        }
        index
    }

    /// Whether some record of `type_id` has this instance id.
    ///
    /// Group is not part of the question: a reference never names one.
    pub fn holds(&self, type_id: u32, instance: u32) -> bool {
        self.by_type
            .get(&type_id)
            .is_some_and(|instances| instances.contains(&instance))
    }

    /// The distinct instance ids of `type_id`.
    pub fn instances_of(&self, type_id: u32) -> Option<&BTreeSet<u32>> {
        self.by_type.get(&type_id)
    }

    /// How many distinct instance ids the index holds, across all types.
    pub fn len(&self) -> usize {
        self.by_type.values().map(BTreeSet::len).sum()
    }

    /// Whether the index holds nothing.
    pub fn is_empty(&self) -> bool {
        self.by_type.is_empty()
    }
}

/// One globals reference slot: which [`CellReferenceField`] reports it, at which
/// index, and what it declares.
struct GlobalsSlot {
    field: CellReferenceField,
    /// The two *start-cell* slots share a field and are told apart by index.
    index: usize,
    target: ReferenceTarget,
}

/// Maps a globals reference-slot name to its reference field and declared target.
///
/// `startingCellKey` is the one slot whose target is
/// [`ReferenceTarget::Untyped`]: the record stores no type word for it, and the
/// value the corpus holds names a `prop`, not a cell. See
/// [`crate::globals::GLOBALS_REFERENCE_FIELDS`].
fn globals_slot(name: &str) -> Option<GlobalsSlot> {
    let typed = |field, index, type_id| {
        Some(GlobalsSlot {
            field,
            index,
            target: ReferenceTarget::Typed(type_id),
        })
    };
    match name {
        "world_1" | "world_2" | "world_3" | "world_4" | "world_5" | "worldBackground_1"
        | "worldBackground_2" | "worldBackground_3" | "worldBackground_4" | "worldBackground_5"
        | "worldRandom" | "worldRandomBg" => typed(
            CellReferenceField::GlobalsWorld,
            0,
            crate::world::WORLD_TYPE,
        ),
        "startCell" => typed(CellReferenceField::GlobalsCell, 0, crate::cell::CELL_TYPE),
        "startingCellKey" => Some(GlobalsSlot {
            field: CellReferenceField::GlobalsCell,
            index: 1,
            target: ReferenceTarget::Untyped,
        }),
        "effectMapEntry" => typed(
            CellReferenceField::GlobalsEffectMap,
            0,
            crate::maps::EFFECT_MAP_TYPE,
        ),
        "backgroundMapEntry" => typed(
            CellReferenceField::GlobalsBackgroundMap,
            0,
            crate::maps::BACKGROUND_MAP_TYPE,
        ),
        "keyLookAlgorithm" => typed(
            CellReferenceField::GlobalsLookAlgorithm,
            0,
            crate::look::LOOK_ALGORITHM_TYPE,
        ),
        _ => None,
    }
}

/// An ordered set of decoded records, with the identity index beside it.
#[derive(Debug, Clone, Default)]
pub struct CellCatalogue {
    index: CellInstanceIndex,
    by_type: BTreeMap<u32, Vec<CellContentRecord>>,
}

impl CellCatalogue {
    /// An empty catalogue. Every resolution fails.
    pub fn new() -> Self {
        Self::default()
    }

    /// Builds a catalogue from decoded records, in iteration order.
    ///
    /// **Duplicates by identity are kept, not dropped.** Two rows with the same
    /// `(type, group, instance)` are a real condition in a patch overlay — the
    /// same record in a base package and in a patch — and the resolver's answer
    /// for an instance that matches two rows is
    /// [`CellReferenceError::Ambiguous`]. Silently keeping one of them would
    /// invent a priority order this crate has no opinion about.
    pub fn from_records<I: IntoIterator<Item = CellContentRecord>>(records: I) -> Self {
        let mut catalogue = Self::new();
        for record in records {
            catalogue.add(record);
        }
        catalogue
    }

    /// Adds one decoded record.
    pub fn add(&mut self, record: CellContentRecord) {
        self.index.insert(record.key);
        self.by_type
            .entry(record.key.type_id)
            .or_default()
            .push(record);
    }

    /// Records an identity whose record has **not** been decoded.
    ///
    /// This is the honest way to feed the catalogue from a package index: the
    /// identity is real, and the absence of a decoded value is a fact rather than
    /// an empty record.
    pub fn add_identity(&mut self, key: ResourceKey) {
        self.index.insert(key);
    }

    /// The identity index.
    pub const fn index(&self) -> &CellInstanceIndex {
        &self.index
    }

    /// Every decoded record of `type_id`, in insertion order.
    pub fn of_type(&self, type_id: u32) -> &[CellContentRecord] {
        self.by_type.get(&type_id).map_or(&[], Vec::as_slice)
    }

    /// How many records have been decoded into this catalogue.
    pub fn record_count(&self) -> usize {
        self.by_type.values().map(Vec::len).sum()
    }

    /// How many distinct instance ids the catalogue knows about.
    pub fn identity_count(&self) -> usize {
        self.index.len()
    }

    /// Whether the catalogue knows about no records at all.
    pub fn is_empty(&self) -> bool {
        self.index.is_empty()
    }

    /// Every decoded record, in `(type, group, instance)` order.
    ///
    /// Deterministic by construction: `BTreeMap` over type id plus a sort of each
    /// type's rows by identity, so a validation report is diffable between runs.
    pub fn sorted(&self) -> Vec<&CellContentRecord> {
        let mut out: Vec<&CellContentRecord> = self.by_type.values().flatten().collect();
        out.sort_by_key(|record| record.key);
        out
    }

    /// Whether some record of `type_id` has this instance id.
    pub fn holds_instance(&self, type_id: u32, instance: u32) -> bool {
        self.index.holds(type_id, instance)
    }
}

/// Resolves references against a [`CellCatalogue`].
#[derive(Debug, Clone, Copy)]
pub struct CellReferenceResolver<'a> {
    catalogue: &'a CellCatalogue,
}

impl<'a> CellReferenceResolver<'a> {
    /// Binds a resolver to a catalogue.
    pub const fn new(catalogue: &'a CellCatalogue) -> Self {
        Self { catalogue }
    }

    /// The catalogue this resolver reads.
    pub const fn catalogue(&self) -> &'a CellCatalogue {
        self.catalogue
    }

    /// Resolves one reference against the catalogue.
    ///
    /// `expected_type` narrows the search when the caller knows what the field
    /// should declare; `None` accepts whatever the record itself declares. It
    /// can only ever *narrow* — a mismatch is
    /// [`CellReferenceError::TargetTypeMismatch`], never a silent override,
    /// because the record is the authority on what its own field means.
    pub fn resolve(
        &self,
        record: &CellContentRecord,
        reference: &CellReference,
        expected_type: Option<u32>,
    ) -> Result<&'a CellContentRecord, CellReferenceError> {
        if !record.key.is_complete() {
            return Err(CellReferenceError::IncompleteSource { key: record.key });
        }
        if !reference.source.is_complete() || reference.source != record.key {
            return Err(CellReferenceError::SourceMismatch {
                key: record.key,
                claimed: reference.source,
            });
        }
        // The record is the authority: a hand-built reference the record does not
        // actually emit is refused rather than resolved. Recovering the emitted
        // reference in the same pass also means the declared target type comes
        // from the record, never from the caller.
        let declared = record
            .references()
            .into_iter()
            .find(|candidate| {
                candidate.field == reference.field
                    && candidate.index == reference.index
                    && candidate.instance == reference.instance
            })
            .map(|candidate| candidate.target)
            .ok_or(CellReferenceError::NotAReference {
                key: record.key,
                field: reference.field,
                index: reference.index,
                instance: reference.instance,
            })?;

        let type_id = match declared {
            ReferenceTarget::Untyped => {
                return Err(CellReferenceError::UnknownTypeWord {
                    key: record.key,
                    field: reference.field,
                    index: reference.index,
                    instance: reference.instance,
                })
            }
            ReferenceTarget::Foreign(type_id) => {
                return Err(CellReferenceError::OutsideFamily {
                    key: record.key,
                    field: reference.field,
                    index: reference.index,
                    type_id,
                })
            }
            ReferenceTarget::Typed(type_id) => type_id,
        };
        if let Some(expected) = expected_type {
            if expected != type_id {
                return Err(CellReferenceError::TargetTypeMismatch {
                    key: record.key,
                    field: reference.field,
                    index: reference.index,
                    requested_type: expected,
                    field_type: type_id,
                });
            }
        }

        let mut found: Option<&CellContentRecord> = None;
        let mut candidates = 0usize;
        for candidate in self.catalogue.of_type(type_id) {
            if candidate.key.instance_id != reference.instance {
                continue;
            }
            candidates += 1;
            if found.is_none() {
                found = Some(candidate);
            }
        }
        match found {
            Some(record) if candidates == 1 => Ok(record),
            Some(_) => Err(CellReferenceError::Ambiguous {
                key: record.key,
                field: reference.field,
                index: reference.index,
                type_id,
                instance: reference.instance,
                candidates,
            }),
            None => Err(CellReferenceError::NotFound {
                key: record.key,
                field: reference.field,
                index: reference.index,
                type_id,
                instance: reference.instance,
            }),
        }
    }

    /// Resolves every reference a record emits, keeping the failures.
    ///
    /// Returns `(resolved, failures)` where each resolved entry is
    /// `(reference, record)` and each failure is `(reference, error)`. Nothing is
    /// dropped: a caller reporting coverage needs to see the non-findings and
    /// the misses in the same place.
    #[allow(clippy::type_complexity)]
    pub fn resolve_all(
        &self,
        record: &CellContentRecord,
    ) -> (
        Vec<(CellReference, &'a CellContentRecord)>,
        Vec<(CellReference, CellReferenceError)>,
    ) {
        let mut resolved = Vec::new();
        let mut failures = Vec::new();
        for reference in record.references() {
            match self.resolve(record, &reference, None) {
                Ok(target) => resolved.push((reference, target)),
                Err(error) => failures.push((reference, error)),
            }
        }
        (resolved, failures)
    }
}
