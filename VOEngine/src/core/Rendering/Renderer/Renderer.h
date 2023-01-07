#pragma once



namespace VOEngine {
	class Renderer {
	public:
		Renderer() {};
		void fill(color AColor) { 
			m_RenderQueue.push_back([this, AColor]() {doFill(AColor);});
		};
		void drawRectangle()   {};
		void drawLine()        {};
		void drawText()        {};
		void drawCircle()      {};
		void drawArc()         {};
		void drawBezier()      {};
		virtual void render()  {
			fill(color(0,0,0,1));
			for (std::function<void(void)> fn: m_RenderQueue) {
				fn();
			}
		};
	private:
		std::vector<std::function<void(void)>> m_RenderQueue;

	protected:
		virtual void doFill(color color) = 0;
		virtual void doDrawRectangle() = 0;
		virtual void doDrawLine() = 0;
		virtual void doDrawText() = 0;
		virtual void doDrawCircle() = 0;
		virtual void doDrawArc() = 0;
		virtual void doDrawBezier() = 0;
		
	};
}


