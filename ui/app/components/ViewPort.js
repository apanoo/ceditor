import React, { Component } from 'react';
import styles from './ViewPort.scss';

type Props = {};

export default class ViewPort extends Component<Props> {
  props: Props;

  render() {
    return <div className={styles.viewport} />;
  }
}
