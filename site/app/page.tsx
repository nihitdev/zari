import Link from "next/link";

const capabilities = [
  ["Navigate", "Vim-style movement, directory history, tabs, bookmarks, and fzf-powered jumps."],
  ["Operate", "Multi-select, copy, move, rename, trash, and collision-safe paste without shell interpolation."],
  ["Preview", "Text and directory views plus optional JSON, PDF, archive, image, and media metadata."],
  ["Customize", "Layered TOML config, remappable key chords, six themes, Nerd Font icons, and live reload."],
];

const keys = [
  ["j / k", "move"], ["h / l", "leave / enter"], ["Space", "select"],
  ["z", "subtree"], ["S", "content search"], ["?", "all bindings"],
];

const integrations = ["fd", "rg", "fzf", "zoxide", "jq", "7-Zip", "Poppler", "FFmpeg", "ImageMagick"];

function Terminal() {
  return <div className="terminal-wrap" aria-label="Illustration of Zari's three-pane interface">
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
  return <main className="landing">
    <section className="landing-hero shell">
      <a className="release-pill" href="https://github.com/nihitdev/zari/releases/latest"><span/> Zari 0.1 is available <b>View release →</b></a>
      <div className="hero-mark" aria-hidden="true">Z</div>
      <h1>Your filesystem.<br/><em>Under your fingers.</em></h1>
      <p>A fast, keyboard-driven terminal file manager for Linux—written in C++20, built on ncursesw, and designed without a plugin runtime.</p>
      <div className="landing-actions">
        <Link className="button primary" href="/docs/getting-started/">Get started <span>→</span></Link>
        <a className="button secondary" href="https://github.com/nihitdev/zari">GitHub <span>↗</span></a>
      </div>
      <div className="command-card"><span>$</span><code>curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh</code></div>
      <p className="install-links"><Link href="/docs/installation/">All installation methods</Link><span>·</span><Link href="/docs/configuration/#generate-starter-files">Run zari init</Link></p>
    </section>

    <section className="landing-terminal shell"><div className="terminal-glow"/><Terminal/></section>

    <section className="project-strip"><div className="shell"><span>LINUX</span><span>C++20</span><span>NCURSESW</span><span>GPL-3.0-OR-LATER</span><span>NO PLUGINS</span></div></section>

    <section className="landing-section shell" id="features">
      <div className="landing-heading"><p>BUILT FOR THE TERMINAL</p><h2>Direct controls.<br/>Useful context.</h2><p>Zari keeps filesystem work visible and predictable while staying close to native Linux tools.</p></div>
      <div className="capability-grid">{capabilities.map(([title,description],index)=><article key={title}><span>0{index+1}</span><h3>{title}</h3><p>{description}</p></article>)}</div>
    </section>

    <section className="keyboard-section">
      <div className="shell"><div><p className="section-label">KEYBOARD FIRST</p><h2>Learn a handful.<br/>Remap everything.</h2><p>Defaults are Vim-like, multi-key chords are first-class, and the help overlay always reflects your active keymap.</p><Link href="/docs/keybindings/">Keybinding reference →</Link></div><div className="key-list">{keys.map(([key,action])=><div key={key}><kbd>{key}</kbd><span>{action}</span></div>)}</div></div>
    </section>

    <section className="landing-section tooling-section shell">
      <div className="landing-heading"><p>OPTIONAL, NOT REQUIRED</p><h2>Native core.<br/>Better together.</h2><p>Zari runs without this toolchain, then detects familiar command-line utilities for richer navigation, search, and previews.</p></div>
      <div className="tool-cloud">{integrations.map(tool=><span key={tool}>{tool}</span>)}</div>
      <Link className="text-link" href="/docs/optional-tools/">Explore optional integrations →</Link>
    </section>

    <section className="open-source-section"><div className="shell"><div className="oss-mark">GPL</div><div><p className="section-label">INDEPENDENT AND OPEN SOURCE</p><h2>Built in the open.<br/>Owned by its users.</h2><p>Zari is an independent implementation licensed under GPL-3.0-or-later. Read the code, report issues, package it, or contribute a focused improvement.</p><div className="landing-actions"><a className="button primary" href="https://github.com/nihitdev/zari">Browse source <span>↗</span></a><Link className="button secondary" href="/docs/development/">Contribute <span>→</span></Link></div></div></div></section>
  </main>;
}
