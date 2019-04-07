import type { Dispatch as ReduxDispatch, Store as ReduxStore } from 'redux';

export type ceditorStateType = {
  +ceditor: number
};

export type Action = {
  +type: string
};

export type GetState = () => ceditorStateType;

export type Dispatch = ReduxDispatch<Action>;

export type Store = ReduxStore<GetState, Action>;
