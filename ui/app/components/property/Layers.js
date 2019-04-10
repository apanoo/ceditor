import React, { Component } from 'react';

import Tree from '../tree/Tree';
import Color from './value/Color';
import Select from './value/Select';
import Value from './value/Value';

import TabList from '../tab/TabList';
import Tab from '../tab/Tab';

import Object from './Object';
import Geometry from './Geometry';
import Material from './Material';

import styles from './Layers.scss';

type Props = {};

export default class Layers extends Component<Props> {
  props: Props;

  onValue = (type, value) => {

  }

  render() {
    return (
      <div className={styles.layers}>
        <div className={styles.main}>
          <Tree />
          <Value title="Background" type='vec4' editable={true} onValue={this.onValue}/>
          <Value title="Fog" type='vec4' editable={true} onValue={this.onValue}/>
        </div>
        <div className={styles.tabs}>
          <TabList scroll={true}>
            <Tab title="Object" content={<Object />} />
            <Tab title="Geometry" content={<Geometry />} />
            <Tab title="Material" content={<Material />} />
          </TabList>
        </div>
      </div>
    );
  }
}
