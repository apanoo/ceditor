import React, { Component } from 'react';

import { Label } from '@blueprintjs/core';

import styles from './Color.scss';

type Props = {
  title: string,
  onChange: value => void
};

export default class Color extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;
  }

  render() {
    const { title, onChange } = this.props;

    return (
      <div className={styles.color}>
        <label>{title}</label>
        <div className={styles.val} />
      </div>
    );
  }
}
