import React, { Component } from 'react';
import MenuBar from './MenuBar';
import ToolBar from './ToolBar';
import MainCanvas from './MainCanvas';
import StatusBar from './StatusBar';

import styles from './Ceditor.scss';

type Props = {
  test: () => void,
  ceditor: number
};

export default class Ceditor extends Component<Props> {
  props: Props;

  render() {
    const { ceditor, test } = this.props;
    return (
      <div className={styles.main}>
        <MenuBar />
        <ToolBar />
        <MainCanvas />
        <StatusBar />
      </div>
    );
  }
}
