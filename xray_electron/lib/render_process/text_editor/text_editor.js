const React = require("react");
const ReactDOM = require("react-dom");
const PropTypes = require("prop-types");
const { styled } = require("styletron-react");
const xray = require("xray");
const TextPlane = require("./text_plane");
const $ = React.createElement;

class TextEditorContainer extends React.Component {
  constructor(props) {
    super(props);
    this.onWheel = this.onWheel.bind(this);

    const buffer = new xray.TextBuffer(1);
    const editor = new xray.TextEditor(buffer, this.editorChanged.bind(this));

    if (props.initialText) {
      props.initialText = props.initialText.repeat(3);
      const step = 500;
      console.log(props.initialText.length / step);
      for (var i = 0; i < props.initialText.length; i += step) {
        const text = props.initialText.slice(i, i + step);
        buffer.splice(i, 0, text);
      }
    }
    //
    for (var i = 0; i < 1000; i++) {
      editor.addSelection({row: i, column: 0}, {row: i, column: 0});
    }

    window.addEventListener('keydown', (event) => {
      switch (event.key) {
        case 'ArrowLeft':
          event.shiftKey ? editor.selectLeft() : editor.moveLeft();
          break;
        case 'ArrowDown':
          if (event.shiftKey) {
            editor.selectDown()
          } else if (event.altKey) {
            editor.addSelectionBelow();
          } else {
            editor.moveDown();
          }
          break;
        case 'ArrowRight':
          event.shiftKey ? editor.selectRight() : editor.moveRight();
          break;
        case 'ArrowUp':
          if (event.shiftKey) {
            editor.selectUp()
          } else if (event.altKey) {
            editor.addSelectionAbove();
          } else {
            editor.moveUp();
          }
          break;
      }
    })

    this.state = {
      resizeObserver: new ResizeObserver((entries) => this.componentDidResize(entries[0].contentRect)),
      editor: editor,
      scrollTop: 0,
      height: 0,
      width: 0,
      editorVersion: 0,
      showCursors: true
    };
  }

  componentDidMount() {
    const element = ReactDOM.findDOMNode(this);
    this.state.resizeObserver.observe(element);
    this.componentDidResize({
      width: element.offsetWidth,
      height: element.offsetHeight
    });

    element.addEventListener('wheel', this.onWheel, {passive: true});

    // this.state.cursorBlinkIntervalHandle = window.setInterval(() => {
    //   this.setState({ showCursors: !this.state.showCursors });
    // }, 500);
  }

  componentWillUnmount() {
    const element = ReactDOM.findDOMNode(this);
    element.removeEventListener('wheel', this.onWheel, {passive: true});
    this.state.editor.destroy();
    this.state.resizeObserver.disconnect();
    window.clearInterval(this.state.cursorBlinkIntervalHandle);
  }

  componentDidResize({width, height}) {
    this.setState({width, height});
  }

  editorChanged() {
    this.setState({
      editorVersion: this.state.editorVersion + 1
    });
  }

  computeFrameState() {
    const { scrollTop, height } = this.state;
    const { fontSize, lineHeight } = this.context.theme.editor;
    return this.state.editor.render({
      scrollTop,
      height,
      lineHeight: fontSize * lineHeight
    });
  }

  render() {
    const { scrollTop, width, height, showCursors } = this.state;

    return $(TextEditor, {
      scrollTop,
      width,
      height,
      showCursors,
      frameState: this.computeFrameState()
    })
  }

  onWheel (event) {
    this.setState({
      scrollTop: Math.max(0, this.state.scrollTop + event.deltaY)
    });
  }
}

TextEditorContainer.contextTypes = {
  theme: PropTypes.object
};

const Root = styled("div", {
  width: "100%",
  height: "100%",
  overflow: "hidden"
});

function TextEditor(props) {
  return $(
    Root,
    {onWheel: props.onWheel},
    $(TextPlane, {
      scrollTop: props.scrollTop,
      width: props.width,
      height: props.height,
      showCursors: props.showCursors,
      frameState: props.frameState
    })
  );
}

module.exports = TextEditorContainer;
