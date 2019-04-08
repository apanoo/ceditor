import React, { Component } from 'react';
import styles from './Geometry.scss';

import Value from './value/Value';

type Props = {};

export default class Geometry extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.geometry}>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
        <Value title="Test">
          <label>ttt</label>
        </Value>
      </div>
    );
  }
}
