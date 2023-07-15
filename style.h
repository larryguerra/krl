const char style_css[] PROGMEM = R"rawliteral(
  body {
    background: rgba(0, 182, 214, 0.5);
    color: #fff;
    font: Arial, sans-serif;
  }

  .logo {
    display: block;
    margin: 0 auto;
  }

  h2 {
    margin: 30px 0;
    font-size: 36px;
    font-weight: 400;
    text-align: center;
  }

  ul {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
  }

  li a {
    font-size: 24px;
    display: block;
    text-align: center;
    padding: 14px 16px;
    text-decoration: none;
  }

  a, a:link, a:hover, a:visited, a:active {
    color: white;
  }

  a:hover {
    color: #eee;
  }

)rawliteral";