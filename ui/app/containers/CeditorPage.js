// @flow
// import React, { Component } from 'react';
import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';

import * as CeditorActions from '../actions/ceditor';
import Ceditor from '../components/Ceditor';

function mapStateToProps(state) {
  return {
    ceditor: state.ceditor
  };
}

function mapDispatchToProps(dispatch) {
  return bindActionCreators(CeditorActions, dispatch);
}

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(Ceditor);
