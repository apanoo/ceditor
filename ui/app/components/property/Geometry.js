import React, { Component } from 'react';
import styles from './Geometry.scss';

import Value from './value/Value';

type Props = {};

export default class Geometry extends Component<Props> {
  props: Props;

  render() {
    return (
      <div className={styles.geometry}>
        <Value title="Position side over" type='vec3' editable={true} onValue={this.onPosition}/>
        <Value title="Color" type='vec3' editable={true} onValue={this.onPosition}/>
        <Value title="Scale" type='vec3' editable={true} onValue={this.onPosition}/>
        <Value title="Radius" type='number' editable={true} onValue={this.onPosition}/>
        <Value title="UUID" type='label' editable={true} onValue={this.onPosition}/>
        <Value title="Background" type='vec4' editable={true} onValue={this.onPosition}/>
        <Value title="Fog settings" type='bool' editable={true} onValue={this.onPosition}/>
      </div>
    );
  }
}
