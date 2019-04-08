import React, { Component } from 'react';

import styles from './Value.scss';

type Props = {
  title: string,
  children: Object,
  onChange: value => void
};

export default class Value extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;
  }

  render() {
    const { title, children, onChange } = this.props;

    return (
      <div className={styles.value}>
        <label>{title}</label>
        {children}
      </div>
    );
  }
}
