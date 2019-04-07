import React, { Component } from 'react';
import { Icon } from '@blueprintjs/core';

type Props = {
  name: string
};

export default class ToolItem extends Component<Props> {
  props: Props;

  render() {
    const { name } = this.props;

    return <Icon icon={name} iconSize={25} />;
  }
}
