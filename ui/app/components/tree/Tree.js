import React, { Component } from 'react';
import styles from './Tree.scss';

type Props = {};

export default class Tree extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.treepanel}>
        <div className={styles.tree} />
      </div>
    );
  }
}
