use std::fmt;

pub type Compare<T> = fn(&T, &T) -> bool;

pub fn select<'v, T>(first: &'v T, second: &'v T, compare: Compare<T>) -> &'v T {
    if compare(first, second) { first } else { second }
}

pub fn min<T: PartialOrd + Clone>(first: &T, second: &T) -> bool { first < second }
pub fn max<T: PartialOrd + Clone>(first: &T, second: &T) -> bool { first > second }

pub trait Container<T> {
    fn name(&self) -> &'static str;
    fn push(&mut self, value: T);
    fn pop(&mut self) -> Option<T>;
    fn extremum(&self) -> Option<&T>;
    fn len(&self) -> usize;
    fn is_empty(&self) -> bool { self.len() == 0 }
}

impl <T> fmt::Debug for Container<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Container {{ name: {}, len: {} }}", self.name(), self.len())
    }
}

impl <T> fmt::Display for Container<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} size {}", self.name(), self.len())
    }
}

#[test]
fn main() {
    assert_eq!(select(&1, &2, min), &1);
    assert_eq!(select(&1, &2, max), &2);

    assert_eq!(select(&"a", &"b", min), &"a");
    assert_eq!(select(&"a", &"b", max), &"b");
}
