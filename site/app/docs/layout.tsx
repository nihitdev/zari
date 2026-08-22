import Link from "next/link";
import { docs } from "@/lib/docs";

export default function DocsLayout({children}:{children:React.ReactNode}) {
  return <div className="docs-shell shell"><aside><Link href="/docs/" className="docs-title">ZARI DOCUMENTATION</Link><Link className="docs-start" href="/docs/getting-started/">Get started →</Link><nav>{docs.map(doc=><Link key={doc.slug} href={`/docs/${doc.slug}/`}>{doc.title}</Link>)}</nav><div className="aside-note"><b>Zari 0.1</b><span>Linux · C++20 · GPL-3.0+</span><a href="https://github.com/nihitdev/zari">Source on GitHub ↗</a></div></aside><main className="docs-main">{children}</main></div>;
}
