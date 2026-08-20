import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import Link from "next/link";
import "./globals.css";

const geist = Geist({ variable: "--font-sans", subsets: ["latin"] });
const mono = Geist_Mono({ variable: "--font-mono", subsets: ["latin"] });

export const metadata: Metadata = {
  title: { default: "Zari — terminal file manager", template: "%s · Zari" },
  description: "A fast, keyboard-driven terminal file manager for Linux, built in modern C++.",
  metadataBase: new URL("https://get-zari.vercel.app"),
  alternates: { canonical: "/" },
  openGraph: { title: "Zari", description: "Move at the speed of thought.", type: "website", url: "https://get-zari.vercel.app" },
};

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return <html lang="en" suppressHydrationWarning><head><meta name="darkreader-lock" content="" /></head><body className={`${geist.variable} ${mono.variable}`}>
    <header className="nav shell">
      <Link href="/" className="brand"><span className="mark">Z</span><span>zari</span></Link>
      <nav aria-label="Main navigation"><Link href="/#features">Features</Link><Link href="/docs/">Docs</Link><a href="https://github.com/nihitdev/zari" target="_blank" rel="noreferrer">GitHub ↗</a></nav>
    </header>
    {children}
    <footer className="footer shell"><div className="brand"><span className="mark small">Z</span><span>zari</span></div><p>Independent. Native. No plugins.</p><p>GPL-3.0-or-later · built with C++20</p></footer>
  </body></html>;
}
