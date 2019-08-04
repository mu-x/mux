use std::collections::VecDeque;

use super::compare::{Compare, Container, select};

pub struct Stack<T> {
    values: VecDeque<T>,
    extremums: VecDeque<T>,
    compare: Compare<T>,
}

impl <T: Clone> Stack<T> {
    pub fn new(compare: Compare<T>) -> Stack<T> {
        return Stack {
            values: VecDeque::new(),
            extremums: VecDeque::new(),
            compare: compare,
        };
    }

    pub fn push(&mut self, value: T) {
        self.values.push_back(value);
        let last = self.values.back().unwrap();
        self.extremums.push_back(match self.extremums.back() {
            None => (*last).clone(),
            Some(current) => (*select(last, current, self.compare)).clone()
        });
    }

    pub fn pop(&mut self) -> Option<T> {
        self.extremums.pop_back();
        return self.values.pop_back();
    }

    pub fn extremum(&self) -> Option<&T> { self.extremums.back() }
    pub fn len(&self) -> usize { self.values.len() }
}

impl <T: Clone> Container<T> for Stack<T> {
    fn name(&self) -> &'static str { "stack" }
    fn push(&mut self, value: T) { self.push(value) }
    fn pop(&mut self) -> Option<T> { self.pop() }
    fn extremum(&self) -> Option<&T> { self.extremum() }
    fn len(&self) -> usize { self.len() }
}

#[test]
fn main() {
    use super::compare::max;
    let mut stack: Box<Container<i32>> = Box::new(Stack::new(max));

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
