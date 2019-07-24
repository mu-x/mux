pub type Compare<T> = fn(&T, &T) -> bool;

pub fn select<'v, T>(first: &'v T, second: &'v T, compare: Compare<T>) -> &'v T {
    if compare(first, second) { first } else { second }
}

pub fn min<T: PartialOrd + Clone>(first: &T, second: &T) -> bool { first < second }
pub fn max<T: PartialOrd + Clone>(first: &T, second: &T) -> bool { first > second }

pub trait InOut<T> {
    fn push(&mut self, value: T);
    fn pop(&mut self) -> Option<T>;
    fn extremum(&self) -> Option<&T>;
    fn len(&self) -> usize;
    fn is_empty(&self) -> bool { self.len() == 0 }
}

#[test]
fn main() {
    assert_eq!(select(&1, &2, min), &1);
    assert_eq!(select(&1, &2, max), &2);

    assert_eq!(select(&"a", &"b", min), &"a");
    assert_eq!(select(&"a", &"b", max), &"b");
}
