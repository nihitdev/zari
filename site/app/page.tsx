import Link from "next/link";

const features = [
  ["01", "Three panes, zero noise", "See where you came from, what is here, and what comes next—without leaving the keyboard."],
  ["02", "Native by design", "Modern C++20 and ncursesw. Fast startup, deterministic cleanup, and no scripting runtime."],
  ["03", "Safe file operations", "Collision-aware copy and move, explicit permanent deletion, and freedesktop-compatible trash."],
  ["04", "Make it yours", "Layered TOML configuration, remappable key chords, six built-in themes, and live reload."],
  ["05", "Tabs with memory", "Every tab keeps its own directory, cursor, history, and selection state."],
  ["06", "Useful previews", "Read text, inspect folders and metadata, and identify binary files without executing arbitrary code."],
];

function Terminal() {
  return <div className="terminal-wrap" aria-label="Illustration of the Zari interface">
    <div className="terminal-bar"><span/><span/><span/><b>zari — ~/Projects/zari</b></div>
    <div className="terminal-tabs"><strong>[1:zari]</strong><span>2:docs</span><span className="terminal-path">~/Projects/zari</span></div>
    <div className="panes">
      <div className="pane parent"><small>PARENT</small><p>▰ Projects</p><p>▰ sandbox</p><p>▰ dotfiles</p><p>▰ archive</p></div>
      <div className="pane current"><small>CURRENT</small><p className="active">› ▰ src/</p><p>  ▰ include/</p><p>  · README.md</p><p>  · CMakeLists.txt</p><p>  · LICENSE</p><p>  * install.sh</p></div>
      <div className="pane preview"><small>PREVIEW · main.cpp</small><pre><i>1</i> <em>#include</em> &lt;iostream&gt;{"\n"}<i>2</i> <em>#include</em> <span>&quot;zari/app.hpp&quot;</span>{"\n"}<i>3</i>{"\n"}<i>4</i> <b>int</b> main(int argc, char** argv) {"{"}{"\n"}<i>5</i>   <b>return</b> zari::App(argc, argv).run();{"\n"}<i>6</i> {"}"}</pre></div>
    </div>
    <div className="status"><b>NORMAL</b><span>0 selected</span><span>12 items</span><span>main.cpp · 612 B · rw-r--r--</span></div>
  </div>;
}

export default function Home() {
  return <main>
    <section className="hero shell">
      <div className="eyebrow"><span/> TERMINAL FILE MANAGER · LINUX</div>
      <h1>Move at the<br/>speed of <em>thought.</em></h1>
      <p className="lede">Zari is a fast, keyboard-driven file manager built in modern C++. Familiar enough to feel natural. Focused enough to stay out of your way.</p>
      <div className="actions"><Link className="button primary" href="/docs/getting-started/">Get started <span>→</span></Link><a className="button secondary" href="https://github.com/nihitdev/zari">View source ↗</a></div>
      <div className="install"><code><span>$</span> git clone https://github.com/nihitdev/zari.git</code><span aria-hidden="true">↵</span></div>
    </section>
    <section className="demo shell"><Terminal/><div className="float-card card-one"><b>VIM-STYLE</b><span><kbd>g</kbd><kbd>g</kbd> jump to top</span></div><div className="float-card card-two"><b>LIVE RELOAD</b><span><kbd>R</kbd> config applied</span></div></section>
    <section className="manifesto shell"><p>FILESYSTEM, UNCOMPLICATED</p><blockquote>Tools should feel like<br/>an extension of your hands.</blockquote><div className="rule"/><p className="manifesto-copy">Zari keeps the feedback loop tight: direct controls, useful context, and no plugin runtime between you and your files.</p></section>
    <section className="features shell" id="features"><div className="section-title"><p>BUILT FOR FLOW</p><h2>Everything you need.<br/><em>Nothing you don’t.</em></h2></div><div className="feature-grid">{features.map(([n,title,text])=><article key={n}><span>{n}</span><h3>{title}</h3><p>{text}</p></article>)}</div></section>
    <section className="themes shell"><div><p className="kicker">YOUR TERMINAL, YOUR RULES</p><h2>Colors with<br/><em>character.</em></h2><p>Start with a carefully tuned preset, then override every surface with a small TOML file.</p><Link href="/docs/configuration/">Explore configuration →</Link></div><div className="swatches"><div className="swatch-title"><span>theme.toml</span><span>● ● ●</span></div>{[["Catppuccin Mocha","catppuccin"],["Gruvbox Dark","gruvbox"],["Dracula","dracula"],["Nord","nord"],["Tokyo Night","tokyo"]].map(([name,slug])=><div className="swatch" key={name}><b>{name}</b><span><i className={`tone ${slug}-one`}/><i className={`tone ${slug}-two`}/><i className={`tone ${slug}-three`}/></span></div>)}</div></section>
    <section className="cta"><div className="shell"><span className="big-z">Z</span><div><p>READY WHEN YOU ARE</p><h2>Your files.<br/>Your flow.</h2><Link className="button light" href="/docs/getting-started/">Build Zari <span>→</span></Link></div></div></section>
  </main>;
}
