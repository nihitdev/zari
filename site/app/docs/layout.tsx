import Link from "next/link";
import { docs } from "@/lib/docs";

export default function DocsLayout({children}:{children:React.ReactNode}) {
  return <div className="docs-shell shell"><aside><Link href="/docs/" className="docs-title">DOCUMENTATION</Link><nav>{docs.map(doc=><Link key={doc.slug} href={`/docs/${doc.slug}/`}>{doc.title}</Link>)}</nav><div className="aside-note"><b>Zari 0.1</b><span>Version one documentation</span></div></aside><main className="docs-main">{children}</main></div>;
}
