# Zari website

Static Next.js website and documentation for Zari.

```sh
npm install
npm run dev
```

Production verification:

```sh
npm run lint
npm run build
```

The build uses `output: "export"`, so Vercel can deploy it without server functions. Set the Vercel Root Directory to `site`. Before publishing, replace the placeholder GitHub URLs and `metadataBase` domain with the real repository and production domain.
