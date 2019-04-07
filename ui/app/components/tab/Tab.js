import React, { Component } from 'react';
import styles from './Tab.scss';

type Props = {
  title: string,
  content: Component
};

export default class Tab extends Component<Props> {
  props: Props;

  render() {
    const { content, title } = this.props;

    return <div className={styles.tab}>{content}</div>;
  }
}
