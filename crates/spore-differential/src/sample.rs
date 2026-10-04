//! Deterministic record sampling.
//!
//! A bounded sample of the real corpus has to be reproducible: a divergence
//! reported from a random draw cannot be re-examined, and a coverage claim
//! cannot be checked. So nothing here uses a random number generator or the
//! clock. The rule is "the first `head` rows, then every `stride`-th after
//! them", which is stable under any change to the corpus and concentrates on
//! the low end of the index -- where the earliest, and historically the most
//! divergent, records live.

/// A deterministic selection of record indices.
///
/// Returns ascending indices in `[0, total)`. When `total <= budget` every index
/// is returned, so the fixture-sized corpus is never sampled.
#[must_use]
pub fn sample_indices(total: usize, budget: usize) -> Vec<usize> {
    if budget == 0 || total == 0 {
        return Vec::new();
    }
    if total <= budget {
        return (0..total).collect();
    }
    // A quarter of the budget on the head, so the earliest records are always
    // covered and a later change to the tail of a package cannot hide the head.
    // The head is never allowed to eat the whole budget: the stride needs at
    // least one tail slot to divide by.
    let head = head_size(budget).min(total);
    let tail_budget = budget.saturating_sub(head).max(1);
    let stride = (total - head).div_ceil(tail_budget);
    let mut indices: Vec<usize> = (0..head).collect();
    let mut index = head;
    while indices.len() < budget && index < total {
        indices.push(index);
        index += stride;
    }
    indices
}

/// How many of `budget` go to the leading run.
fn head_size(budget: usize) -> usize {
    // `budget / 4`, but never zero (a zero-length head samples nothing) and
    // never the whole budget (see above). A budget of 1 or 2 is therefore spent
    // entirely on the head, which is the honest reading of "draw at most one".
    match budget {
        0 => 0,
        1..=2 => budget,
        _ => (budget / 4).max(1),
    }
}

/// How a sample was drawn, for a report note.
#[must_use]
pub fn describe_sample(total: usize, budget: usize, taken: usize) -> String {
    if total <= budget {
        return format!("every one of the {total} record(s); the budget was {budget}");
    }
    let head = head_size(budget);
    let stride = (total - head).div_ceil(budget.saturating_sub(head).max(1));
    format!(
        "{taken} of {total} record(s): the first {head}, then every {stride}th after them \
         (deterministic; no random draw, so any reported divergence can be re-run)"
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_sample_is_ascending_unique_and_inside_the_range() {
        for total in [0usize, 1, 5, 200, 17119] {
            for budget in [1usize, 2, 7, 200, 500] {
                let indices = sample_indices(total, budget);
                assert!(
                    indices.windows(2).all(|pair| pair[0] < pair[1]),
                    "not ascending/unique for total={total} budget={budget}: {indices:?}"
                );
                assert!(indices.iter().all(|index| *index < total));
                assert!(indices.len() <= budget.max(1).min(total));
                assert!(indices.len() <= total);
            }
        }
    }

    #[test]
    fn a_sample_is_the_same_every_time_it_is_taken() {
        assert_eq!(sample_indices(17119, 200), sample_indices(17119, 200));
    }

    #[test]
    fn a_small_corpus_is_never_sampled() {
        assert_eq!(sample_indices(3, 200), vec![0, 1, 2]);
        assert_eq!(sample_indices(3, 3), vec![0, 1, 2]);
    }

    #[test]
    fn the_head_is_always_covered_and_the_stride_is_positive() {
        let indices = sample_indices(17119, 200);
        assert!(indices.len() >= 190, "took {} of 200", indices.len());
        assert_eq!(&indices[..4], &[0, 1, 2, 3]);
        assert!(indices.last().is_some_and(|last| *last > 16_000));
    }

    #[test]
    fn a_zero_budget_selects_nothing_rather_than_panicking() {
        assert!(sample_indices(100, 0).is_empty());
    }

    #[test]
    fn the_description_states_how_many_and_whether_it_was_the_whole_set() {
        assert!(describe_sample(3, 200, 3).contains("every one of the 3"));
        let described = describe_sample(17119, 200, 200);
        assert!(described.contains("200 of 17119"), "{described}");
        assert!(described.contains("deterministic"), "{described}");
    }
}
