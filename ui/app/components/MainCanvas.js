import React, { Component } from 'react';
import styles from './MainCanvas.scss';

import ViewPort from './ViewPort';
import Property from './Property';

type Props = {};

export default class MainCanvas extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.mainCanvas}>
        <div className={styles.viewport}>
          <ViewPort />
        </div>
        <div className={styles.property}>
          <Property />
        </div>
      </div>
    );
  }
}
