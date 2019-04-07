import React, { Component } from 'react';
import styles from './Object.scss';

type Props = {};

export default class Object extends Component<Props> {
  props: Props;

  render() {
    return <div className={styles.object}>object</div>;
  }
}
