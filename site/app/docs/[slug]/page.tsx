import type { Metadata } from "next";
import Link from "next/link";
import { notFound } from "next/navigation";
import { docs, getDoc } from "@/lib/docs";

export function generateStaticParams(){return docs.map(({slug})=>({slug}));}
export async function generateMetadata({params}:{params:Promise<{slug:string}>}):Promise<Metadata>{const {slug}=await params;const doc=getDoc(slug);return doc?{title:doc.title,description:doc.summary}:{};}

const sectionId = (title:string) => title
  .toLowerCase()
  .replace(/[^a-z0-9]+/g,"-")
  .replace(/^-|-$/g,"");

export default async function DocPage({params}:{params:Promise<{slug:string}>}){const {slug}=await params;const doc=getDoc(slug);if(!doc)notFound();const index=docs.findIndex(item=>item.slug===slug);const previous=docs[index-1],next=docs[index+1];return <article className="doc"><p className="doc-eyebrow">GUIDE · {String(index+1).padStart(2,"0")}</p><h1>{doc.title}</h1><p className="doc-intro">{doc.summary}</p>{doc.sections.map(section=>{const id=sectionId(section.title);return <section key={section.title} id={id}><h2><a href={`#${id}`}>{section.title}</a></h2>{section.paragraphs?.map(text=><p key={text}>{text}</p>)}{section.bullets&&<ul>{section.bullets.map(item=><li key={item}>{item}</li>)}</ul>}{section.code&&<pre><code>{section.code}</code></pre>}</section>})}<nav className="doc-pager">{previous?<Link href={`/docs/${previous.slug}/`}>← {previous.title}</Link>:<span/>}{next&&<Link href={`/docs/${next.slug}/`}>{next.title} →</Link>}</nav></article>}
