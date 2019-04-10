import React, { Component } from 'react';

import { Checkbox, Icon, InputGroup, Switch, Classes, Popover, Button, MenuItem, Menu, MenuDivider, Position } from '@blueprintjs/core';

import styles from './Value.scss';

/** Value Props =>
 * `type` can set value type and get value in onValue callback
 * `vec2[] - bool[]` is the item `array` object
  +-------+----------------------------------------------------------+
  |  type |   vec2      vec3       vec4    string     enum    bool   |
  |-------|----------------------------------------------------------|
  |       |           position                                       |
  |       |                                                          |
  |       |direction   scale      color     label    select   check  |
  |       |                                                          |
  |       |           rotation                                       |
  |-------|----------------------------------------------------------+
  |  type | vec2[]     vec3[]     vec4[]  string[]   enum[]   bool[] |
  |-------|----------------------------------------------------------|
  |       |                       array  type                        |
  +-------+----------------------------------------------------------+
**/
type Props = {
  title: string,
  type: string,
  editable: boolean,
  onValue: value => void
};

export default class Value extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;
  }

  calValueView = (type) => {
    const exampleMenu = (
      <Menu className={styles.menu}>
        <MenuItem icon="graph" text="Graph" />
        <MenuItem icon="map" text="Map" />
        <MenuItem icon="th" text="Table" shouldDismissPopover={false} />
      </Menu>
  );

    switch (type) {
      case 'vec3': // position scale rotation
        return (
          <ul>
            <li><label>{"1.40"}</label></li>
            <li><label>{"3.02"}</label></li>
            <li><label>{"0.15"}</label></li>
          </ul>
        );
      case 'number':
        return (
          <ul>
            <li><label>{"1.00"}</label></li>
          </ul>
        );
      case 'label':
        return (
          <ul>
            <li><label>{"17B3A148-BFFF-4AE8-A85C-C6F41631A397"}</label></li>
          </ul>
        );
      case 'vec4':   // color
        return (
          <ul>
            <li><span className={styles.color}></span></li>
          </ul>
        );
      case 'bool':
        return (
          <ul className={Classes.DARK}>
            <li><Checkbox className={styles.checkbox}/></li>
          </ul>
        );
      case 'enum':
        return (
          <ul className={Classes.DARK}>
            <li>
            <Popover className={styles.popover} content={exampleMenu} position={Position.TOP}>
              <Button icon='share' text="Open..." />
            </Popover>
            </li>
          </ul>
        );
      case 'toggle':
        return (
          <ul className={Classes.DARK}>
            <li>
            <Switch className={styles.toggle} id="text-input" label="" disabled={false} />
            </li>
          </ul>
        );
      case 'vec2':
        return (
          <ul>
            <li><label>{"1.40"}</label></li>
            <li><label>{"3.02"}</label></li>
          </ul>
        );
      case 'string':
        return (
          <ul className={Classes.DARK}>
            <li>
            <InputGroup
              className={styles.string}
              disabled={false}
              large={false}
              onChange={()=>{}}
              placeholder="Filter histogram..."
              rightElement={undefined}
              small={false}
              value={"32244"}
            />
            </li>
          </ul>
        );
      default:
        return undefined;
    }
  }

  render() {
    const { title, children, onValue, type } = this.props;

    return (
      <div className={styles.value}>
        <label>{title}</label>
        {this.calValueView(type)}
      </div>
    );
  }
}
