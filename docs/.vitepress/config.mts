import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "ToolExample",
  description: "UX/UI C/C++ examples for Unreal Engine editor tools",
  base: '/ToolExample/',
  themeConfig: {
    nav: [
      { text: 'Home', link: '/' },
      { text: 'GitHub', link: 'https://github.com/ScottKirvan/ToolExample' }
    ],
    socialLinks: [
      { icon: 'github', link: 'https://github.com/ScottKirvan/ToolExample' },
      { icon: 'discord', link: 'https://discord.gg/TN6XJSNK5Y' }
    ]
  }
})
