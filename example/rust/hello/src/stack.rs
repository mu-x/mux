use std::collections::VecDeque;

use super::compare::{Compare, InOut, select};

pub struct ExtremumStack<T> {
    values: VecDeque<T>,
    extremums: VecDeque<T>,
    compare: Compare<T>,
}

#[allow(dead_code)]
impl <T: Clone> ExtremumStack<T> {
    pub fn new(compare: Compare<T>) -> ExtremumStack<T> {
        return ExtremumStack {
            values: VecDeque::new(),
            extremums: VecDeque::new(),
            compare: compare,
        };
    }

    fn push(&mut self, value: T) {
        self.values.push_back(value);
        let last = self.values.back().unwrap();
        self.extremums.push_back(match self.extremums.back() {
            None => (*last).clone(),
            Some(current) => (*select(last, current, self.compare)).clone()
        });
    }

    fn pop(&mut self) -> Option<T> {
        self.extremums.pop_back();
        return self.values.pop_back();
    }

    fn extremum(&self) -> Option<&T> { self.extremums.back().map(|value| value) }
    fn len(&self) -> usize { self.values.len() }
}

#[allow(dead_code)]
impl <T: Clone> InOut<T> for ExtremumStack<T> {
    fn push(&mut self, value: T) { self.push(value) }
    fn pop(&mut self) -> Option<T> { self.pop() }
    fn extremum(&self) -> Option<&T> { self.extremum() }
    fn len(&self) -> usize { self.len() }
}

#[test]
fn main() {
    use super::compare::max;
    let mut stack: Box<InOut<i32>> = Box::new(ExtremumStack::new(max));

    stack.push(3);
    assert_eq!(stack.extremum(), Some(&3));

    stack.push(5);
    assert_eq!(stack.extremum(), Some(&5));

    stack.push(2);
    assert_eq!(stack.extremum(), Some(&5));

    stack.push(7);
    assert_eq!(stack.extremum(), Some(&7));

    assert_eq!(stack.pop(), Some(7));
    assert_eq!(stack.extremum(), Some(&5));

    assert_eq!(stack.pop(), Some(2));
    assert_eq!(stack.extremum(), Some(&5));

    assert_eq!(stack.pop(), Some(5));
    assert_eq!(stack.extremum(), Some(&3));

    stack.push(1);
    assert_eq!(stack.extremum(), Some(&3));
}
