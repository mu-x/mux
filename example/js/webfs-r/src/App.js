import React from 'react'
import Browser from './components/Browser'
import './App.css';

class App extends React.Component {
  render() {
    return (
      <div className="App">
        <div className="ribbon">
          <h1>Web FS</h1>
        </div>
        <Browser />
        <div className="ribbon">
          See <a href="https://github.com/mu-x/mux">https://github.com/mu-x/mux</a>
        </div>
      </div>
    );
  }
}

export default App;
