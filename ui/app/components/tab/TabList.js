import React, { Component } from 'react';
import styles from './TabList.scss';

type Props = {
  // component children
  children: Array
};

export default class TabList extends Component<Props> {
  props: Props;

  constructor(props) {
    super(props);
    this.props = props;
    // current select index
    this.state = {
      select: 0
    };
  }

  componentDidMount() {
    const { children } = this.props;

    // cal titles map
    let idx = 0;
    const titles = {};
    React.Children.forEach(children, child => {
      titles[idx] = child.props.title;
      idx += 1;
    });
    this.titles = titles;
    this.setState({ titles });
  }

  onTabClick(e, child) {
    const { titles } = this.state;

    if (!titles) return;
    let idx = 0;
    while (titles[idx]) {
      if (child.props.title === titles[idx] && this.select !== idx) {
        this.setState({ select: idx });
      }
      idx += 1;
    }
  }

  render() {
    const { children } = this.props;
    const { select, titles } = this.state;
    const onTabClick = this.onTabClick.bind(this);

    return (
      <div className={styles.tabs}>
        <div className={styles.tablist}>
          {React.Children.map(children, child => (
            <button
              type="button"
              onClick={e => {
                onTabClick(e, child);
              }}
              className={
                titles && titles[select] === child.props.title
                  ? styles.active
                  : ''
              }
            >
              {child.props.title}
            </button>
          ))}
        </div>
        {select !== undefined &&
          children[select] &&
          children[select].props.content}
      </div>
    );
  }
}
