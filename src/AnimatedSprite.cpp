#include <aSFML/AnimatedSprite.hpp>
/*
sf::AnimatedSprite::AnimatedSprite()
{
}

sf::AnimatedSprite::~AnimatedSprite()
{
}

bool sf::AnimatedSprite::LoadFromFile(const std::string& filePath)
{
	try
	{
		m_animations.clear();

		// Load Document
		ticpp::Document document(filePath);
		document.LoadFile();

		// AnimatedSprite attributes
		for (ticpp::Iterator<ticpp::Attribute> attribute = attribute.begin(document.FirstChildElement()); attribute != attribute.end(); attribute++)
		{
			std::string name = attribute->Name();
			if(name == "image")
				m_image.LoadFromFile(attribute->Value());
		}

		// Count animations and reserve space
		unsigned int animationCount = 0;
		for(ticpp::Iterator<ticpp::Element> animation = animation.begin(document.FirstChildElement()); animation != animation.end(); animation++)
			animationCount++;
		m_animations.reserve(animationCount);

		// Animations
		for(ticpp::Iterator<ticpp::Element> animation = animation.begin(document.FirstChildElement()); animation != animation.end(); animation++)
		{
			m_animations.push_back(Animation());

			bool loop = false;
			bool autoplay = false;

			// Animation attributes
			for(ticpp::Iterator<ticpp::Attribute> attribute = attribute.begin(&*animation); attribute != attribute.end(); attribute++)
			{
				std::string name = attribute->Name();
				if(name == "loop")
					attribute->GetValue(&loop);
				if(name == "autoplay")
					attribute->GetValue(&autoplay);
			}

			// Count frames and reserve space
			unsigned int frameCount = 0;
			for(ticpp::Node* child = animation->FirstChild(false); child; child = child->NextSibling(false))
				frameCount++;
			m_animations.back().frames.reserve(frameCount);

			// Frames
			for(ticpp::Node* frame = animation->FirstChild(false); frame; frame = frame->NextSibling(false))
			{
				// Frame attributes
				std::string rect = frame->ToElement()->GetAttributeOrDefault("rect", "");
				std::string origin = frame->ToElement()->GetAttributeOrDefault("origin", "");

				std::cout << rect << ";" << origin << std::endl;
			}
		}

	}
	catch(ticpp::Exception& ex)
	{
		std::cerr << ex.what();
	}

	
	ticpp::Iterator<ticpp::Element> child;
	for (child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
	{
		std::string strName;
		std::string strValue;
		child->GetValue(&strName);

		ticpp::Iterator< ticpp::Attribute > attribute;
		for (attribute = attribute.begin(child.Get()); attribute != attribute.end();
				attribute++)
		{
			attribute->GetName(&strName);
			attribute->GetValue(&strValue);
			std::cout << strName << ": " << strValue << std::endl;
		}
		std::cout << std::endl;
	}

	return false;
}

void sf::AnimatedSprite::Draw(sf::RenderWindow& window)
{
}*/
