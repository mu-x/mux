use super::compare::{Compare, InOut, select};
use super::stack::ExtremumStack;

pub struct ExtremumQueue<T> {
    ins: ExtremumStack<T>,
    outs: ExtremumStack<T>,
    compare: Compare<T>,
}

#[allow(dead_code)]
impl <T: Clone> ExtremumQueue<T> {
    pub fn new(compare: Compare<T>) -> ExtremumQueue<T> {
        return ExtremumQueue {
            ins: ExtremumStack::<T>::new(compare),
            outs: ExtremumStack::<T>::new(compare),
            compare: compare,
        };
    }

    fn push(&mut self, value: T) {
        self.ins.push(value)
    }

    fn pop(&mut self) -> Option<T> {
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

    fn extremum(&self) -> Option<&T> {
        return match (self.ins.extremum(), self.outs.extremum()) {
            (None, None) => None,
            (Some(first), None) => Some(first),
            (None, Some(second)) => Some(second),
            (Some(first), Some(second)) => Some(select(first, second, self.compare)),
        }
    }

    fn len(&self) -> usize {
        self.ins.len() + self.outs.len()
    }
}

#[allow(dead_code)]
impl <T: Clone> InOut<T> for ExtremumQueue<T> {
    fn push(&mut self, value: T) { self.push(value) }
    fn pop(&mut self) -> Option<T> { self.pop() }
    fn extremum(&self) -> Option<&T> { self.extremum() }
    fn len(&self) -> usize { self.len() }
}

#[test]
fn main() {
    use super::compare::min;
    let mut stack: Box<InOut<i32>> = Box::new(ExtremumQueue::new(min));

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
