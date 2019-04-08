import React, { Component } from 'react';

import { Menu, MenuDivider, MenuItem, Icon } from '@blueprintjs/core';
import getRandomInt from '../../utils/uuid';

import MenuBarConstants from '../../constants/menu';
import styles from './Menu.scss';

type Props = {
  left: number,
  top: number,
  visiable: boolean,
  title: string
};

export default class MenuPanel extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;

    // all menus data from menu.json: title => children
    this.menus = {};
  }

  componentWillMount() {
    // set menu data to this.menus
    MenuBarConstants.menuBarItems.forEach(item => {
      this.menus[item.title] = item.children;
    });
  }

  // calculate menu items
  calMenus = childs => {
    if (!childs) return undefined;
    return childs.map(item => {
      // parse child
      switch (item.type) {
        case 'menu':
          if (item.children && item.children.length > 0) {
            return (
              <MenuItem
                key={item.text + getRandomInt(1000).toString()}
                icon={item.ficon}
                labelElement={<Icon icon={item.sicon} />}
                text={item.text}
              >
                <div className={styles.submenu}>
                  {this.calMenus(item.children)}
                </div>
              </MenuItem>
            );
          }
          return (
            <MenuItem
              key={item.text + getRandomInt(1000).toString()}
              icon={item.ficon}
              labelElement={<Icon icon={item.sicon} />}
              text={item.text}
            />
          );
        case 'devider':
          return (
            <MenuDivider
              key={item.type + getRandomInt(1000).toString()}
              className={styles.divider}
            />
          );
        default:
          return undefined;
      }
    });
  };

  render() {
    const { left, top, visiable, title } = this.props;

    const extStyle = {
      left,
      top,
      display: visiable ? 'block' : 'none'
    };

    return (
      <div className={styles.menupanel} style={extStyle}>
        <div className={styles.menus}>
          <Menu className={styles.menubg}>
            {this.calMenus(this.menus[title])}
          </Menu>
        </div>
      </div>
    );
  }
}
