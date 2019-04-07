import React, { Component } from 'react';
import styles from './Menu.scss';

type Props = {
  left: number,
  top: number,
  visiable: boolean
};

export default class Menu extends Component<Props> {
  props: Props;

  render() {
    const { left, top, visiable } = this.props;

    const extStyle = {
      left,
      top,
      display: visiable ? 'block' : 'none'
    };

    return <div className={styles.menu} style={extStyle} />;
  }
}
