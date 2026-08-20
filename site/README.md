# Zari website

Static Next.js website and documentation for Zari.

Production: [get-zari.vercel.app](https://get-zari.vercel.app)

```sh
npm install
npm run dev
```

Production verification:

```sh
npm run lint
npm run build
```

The build uses `output: "export"`, so Vercel can deploy it without server functions. Set the Vercel Root Directory to `site`.
