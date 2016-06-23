#pragma once

class LPainter;
class LRenderLayer
{
public:
	LRenderLayer();
	virtual ~LRenderLayer();

	virtual void draw(LPainter& painter) = 0;

public:
	template <typename Iterator>
	static void autoDraw(LPainter& painter, Iterator begin, Iterator end)
	{
		typedef std::vector<IDrawableObj*> RenderItems;
		typedef std::map<RenderArgument, RenderItems> RenderQueue;
		RenderQueue renderQueue;

		for (Iterator iter = begin; iter != end; ++iter)
		{
			const RenderArgument& arg = (*iter)->GetRenderArgument();
			renderQueue[arg].push_back(*iter);
		}

		for (RenderQueue::iterator iterChannel = renderQueue.begin();
			iterChannel != renderQueue.end(); ++iterChannel)
		{
			painter.save();
			painter.setPaintArgument(iterChannel->first.paintArg);

			RenderItems& items = iterChannel->second;
			for (RenderItems::iterator iterItem = items.begin();
				iterItem != items.end(); ++iterItem)
			{
				(*iterItem)->draw(painter);
			}
			painter.restore();
		}
	}
};
