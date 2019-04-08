import React, { Component } from 'react';

import styles from './Select.scss';

type Props = {
  title: string,
  onChange: value => void
};

export default class Select extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;
  }

  render() {
    const { title, onChange } = this.props;

    return (
      <div className={styles.select}>
        <label>{title}</label>
        <div className={styles.val} />
      </div>
    );
  }
}
