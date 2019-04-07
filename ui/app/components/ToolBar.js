import React, { Component } from 'react';

import styles from './ToolBar.scss';
import cstyles from './common.scss';

import ToolItem from './ToolItem';

type Props = {
  playing: boolean
};

export default class ToolBar extends Component<Props> {
  props: Props;

  render() {
    const { playing } = this.props;

    return (
      <div className={styles.toolbar}>
        <ol>
          <li>
            <ToolItem name="document-open" />
          </li>
          <li>
            <ToolItem name="new-object" />
          </li>
          <li>
            {playing ? <ToolItem name="pause" /> : <ToolItem name="play" />}
          </li>
          <li>
            <ToolItem name="settings" />
          </li>
        </ol>
        <div className={cstyles.br} />
      </div>
    );
  }
}
