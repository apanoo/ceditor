import React, { Component } from 'react';
import { Icon, Label } from '@blueprintjs/core';

import styles from './StatusBar.scss';

type Props = {};

export default class StatusBar extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.statusBar}>
        <ul>
          <li>
            <Icon icon="cube" iconSize={14} />
          </li>
          <li>
            <Label> Main scene </Label>
          </li>
          <li style={{ float: 'right' }}>
            <Icon icon="git-repo" iconSize={14} />
          </li>
        </ul>
      </div>
    );
  }
}
