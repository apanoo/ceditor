import React, { Component } from 'react';
import styles from './Layers.scss';

type Props = {};

export default class Layers extends Component<Props> {
  props: Props;

  render() {
    return <div className={styles.layers}>layers</div>;
  }
}
