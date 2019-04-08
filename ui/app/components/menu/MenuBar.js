import React, { Component } from 'react';
import styles from './MenuBar.scss';

import MenuPanel from './menu';

import MenuBarConstants from '../../constants/menu';

type Props = {};

export default class MenuBar extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;

    this.state = {
      left: 0,
      top: 0,
      visiable: false,
      current: undefined
    };
  }

  handleClick = () => {
    const { visiable } = this.state;

    if (visiable) {
      this.setState(
        {
          visiable: false
        },
        () => {
          document.removeEventListener('click', this.handleClick);
        }
      );
    }
  };

  onMenuBarItemClick = e => {
    const { current, visiable } = this.state;

    let tvisiable = false;
    if (current !== e.target) {
      // click another item
      tvisiable = true;
    } else {
      tvisiable = !visiable; // click current item again
    }
    this.setState(
      {
        // update current item & visiable
        current: e.target,
        visiable: tvisiable
      },
      () => {
        if (tvisiable) {
          document.addEventListener('click', this.handleClick);
        } else {
          document.removeEventListener('click', this.handleClick);
        }
      }
    );
  };

  onMenuBarItemMouseOver = e => {
    const rect = e.target.getBoundingClientRect();
    const x = rect.left;
    const y = rect.top + rect.height;
    this.setState({
      left: x,
      top: y,
      current: e.target // update current item
    });
  };

  render() {
    const { left, top, visiable, current } = this.state;

    return (
      <div className={styles.menubar}>
        <ol>
          {MenuBarConstants.menuBarItems.map(item => (
            <li
              className={
                visiable &&
                current &&
                current.outerText.toLowerCase() === item.title.toLowerCase()
                  ? styles.active
                  : ''
              }
              key={item.title}
              onClick={e => {
                this.onMenuBarItemClick(e);
              }}
              onMouseOver={e => {
                this.onMenuBarItemMouseOver(e);
              }}
              onFocus={() => {}}
            >
              {item.title}
            </li>
          ))}
        </ol>
        <MenuPanel
          left={left}
          top={top}
          visiable={visiable}
          title={current && current.outerText.toLowerCase()}
        />
      </div>
    );
  }
}
