import React, { Component } from 'react';

import Value from './value/Value';

import styles from './Object.scss';

type Props = {};

export default class Object extends Component<Props> {
  props: Props;

  onValue = (type, value) => {
    console.log("type: ", type, ",value: ", value);
  }

  render() {
    return (
      <div className={styles.object}>
        <Value title="Background" type='vec4' editable={true} onValue={this.onValue}/>
        <Value title="Fog settings" type='bool' editable={true} onValue={this.onValue}/>
        <Value title="Fog selecting" type='enum' editable={true} onValue={this.onValue}/>
        <Value title="Toggle" type='toggle' editable={true} onValue={this.onValue}/>
        <Value title="Vector2" type='vec2' editable={true} onValue={this.onValue}/>
        <Value title="String Input" type='string' editable={true} onValue={this.onValue}/>
      </div>
    );
  }
}
