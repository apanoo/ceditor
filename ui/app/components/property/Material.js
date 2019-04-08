import React, { Component } from 'react';
import styles from './Material.scss';

type Props = {};

export default class Material extends Component<Props> {
  props: Props;

  render() {
    return <div className={styles.material}>material</div>;
  }
}
