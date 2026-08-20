import Link from "next/link";
import { docs } from "@/lib/docs";

export const metadata = { title: "Documentation" };

export default function DocsIndex(){return <><p className="doc-eyebrow">ZARI WIKI</p><h1>Documentation</h1><p className="doc-intro">Everything you need to build, configure, and use Zari without leaving the keyboard.</p><div className="docs-grid">{docs.map((doc,i)=><Link key={doc.slug} href={`/docs/${doc.slug}/`}><span>0{i+1}</span><h2>{doc.title}</h2><p>{doc.summary}</p><b>Read guide →</b></Link>)}</div></>}
