import React, { Component } from 'react';
import styles from './Property.scss';

import TabList from './tab/TabList';
import Tab from './tab/Tab';

// property item
import Layers from './property/Layers';
import Settings from './property/Settings';
import Object from './property/Object';

type Props = {};

export default class Property extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.property}>
        <TabList>
          <Tab title="Layers" content={<Layers />} />
          <Tab title="Object" content={<Object />} />
          <Tab title="Settings" content={<Settings />} />
        </TabList>
      </div>
    );
  }
}
