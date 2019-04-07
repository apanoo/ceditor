// @flow
import { TEST_CEDITOR } from '../actions/ceditor';
import type { Action } from './types';

export default function ceditor(state: number = 0, action: Action) {
  switch (action.type) {
    case TEST_CEDITOR:
      return state + 1;
    default:
      return state;
  }
}
