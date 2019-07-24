use std::collections::VecDeque;

// TODO: Add comparator to select between min/max.
pub struct ExtremumStack<T> {
    values: VecDeque<T>,
    extremums: VecDeque<T>,
}

#[allow(dead_code)]
impl <T: std::cmp::PartialOrd + std::clone::Clone> ExtremumStack<T> {
    pub fn new() -> ExtremumStack<T> {
        return ExtremumStack { values: VecDeque::new(), extremums: VecDeque::new() };
    }

    pub fn len(&self) -> usize {
        return self.values.len();
    }

    pub fn peek(&self) -> Option<&T> {
        return self.values.back();
    }

    pub fn extremum(&self) -> Option<&T> {
        return self.extremums.back().map(|value| value);
    }

    pub fn push(&mut self, value: T) {
        self.values.push_back(value);
        let last = self.values.back().unwrap();
        let extremum = (*
            match self.extremums.back() {
                Some(current) => if last > current { last } else { current },
                None => last,
            }
        ).clone();
        self.extremums.push_back(extremum);
    }

    pub fn pop(&mut self) -> Option<T> {
        self.extremums.pop_back();
        return self.values.pop_back();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn push_pop() {
        let mut stack = ExtremumStack::new();

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
}
