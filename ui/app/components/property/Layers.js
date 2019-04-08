import React, { Component } from 'react';

import Tree from '../tree/Tree';
import Color from './value/Color';
import Select from './value/Select';

import TabList from '../tab/TabList';
import Tab from '../tab/Tab';

import Object from './Object';
import Geometry from './Geometry';
import Material from './Material';

import styles from './Layers.scss';

type Props = {};

export default class Layers extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.layers}>
        <div className={styles.main}>
          <Tree />
          <Color title="Background" />
          <Select title="Fog" />
        </div>
        <div className={styles.tabs}>
          <TabList scroll>
            <Tab title="Object" content={<Object />} />
            <Tab title="Geometry" content={<Geometry />} />
            <Tab title="Material" content={<Material />} />
          </TabList>
        </div>
      </div>
    );
  }
}
