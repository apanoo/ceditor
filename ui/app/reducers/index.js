// @flow
import { combineReducers } from 'redux';
import { connectRouter } from 'connected-react-router';
import ceditor from './ceditor';

export default function createRootReducer(history: History) {
  return combineReducers({
    router: connectRouter(history),
    ceditor
  });
}
