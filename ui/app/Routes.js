import React from 'react';
import { Switch, Route } from 'react-router';
import routes from './constants/routes';
import App from './containers/App';
import CeditorPage from './containers/CeditorPage';

export default () => (
  <App>
    <Switch>
      <Route path={routes.HOME} component={CeditorPage} />
    </Switch>
  </App>
);
