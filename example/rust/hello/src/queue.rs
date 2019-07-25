use super::compare::{Compare, Container, select};
use super::stack::Stack;

pub struct Queue<T> {
    ins: Stack<T>,
    outs: Stack<T>,
    compare: Compare<T>,
}

#[allow(dead_code)]
impl <T: Clone> Queue<T> {
    pub fn new(compare: Compare<T>) -> Queue<T> {
        return Queue {
            ins: Stack::<T>::new(compare),
            outs: Stack::<T>::new(compare),
            compare: compare,
        };
    }

    pub fn push(&mut self, value: T) {
        self.ins.push(value)
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.outs.is_empty() {
            loop {
                match self.ins.pop() {
                    Some(value) => self.outs.push(value),
                    None => break,
                }
            }
        }
        return self.outs.pop();
    }

    pub fn extremum(&self) -> Option<&T> {
        return match (self.ins.extremum(), self.outs.extremum()) {
            (None, None) => None,
            (Some(first), None) => Some(first),
            (None, Some(second)) => Some(second),
            (Some(first), Some(second)) => Some(select(first, second, self.compare)),
        }
    }

    pub fn len(&self) -> usize {
        self.ins.len() + self.outs.len()
    }
}

#[allow(dead_code)]
impl <T: Clone> Container<T> for Queue<T> {
    fn push(&mut self, value: T) { self.push(value) }
    fn pop(&mut self) -> Option<T> { self.pop() }
    fn extremum(&self) -> Option<&T> { self.extremum() }
    fn len(&self) -> usize { self.len() }
}

#[test]
fn main() {
    use super::compare::min;
    let mut stack: Box<Container<i32>> = Box::new(Queue::new(min));

    stack.push(3);
    assert_eq!(stack.extremum(), Some(&3));

    stack.push(5);
    assert_eq!(stack.extremum(), Some(&3));

    stack.push(2);
    assert_eq!(stack.extremum(), Some(&2));

    stack.push(7);
    assert_eq!(stack.extremum(), Some(&2));

    assert_eq!(stack.pop(), Some(3));
    assert_eq!(stack.extremum(), Some(&2));

    assert_eq!(stack.pop(), Some(5));
    assert_eq!(stack.extremum(), Some(&2));

    assert_eq!(stack.pop(), Some(2));
    assert_eq!(stack.extremum(), Some(&7));

    stack.push(1);
    assert_eq!(stack.extremum(), Some(&1));
}
