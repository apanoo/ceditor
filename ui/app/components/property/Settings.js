import React, { Component } from 'react';
import styles from './Settings.scss';

type Props = {};

export default class Settings extends Component<Props> {
  props: Props;

  render() {
    return <div className={styles.settings}>settings</div>;
  }
}
