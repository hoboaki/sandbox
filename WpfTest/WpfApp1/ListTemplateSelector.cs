using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;

namespace WpfApp1
{
    public class ListTemplateSelector : DataTemplateSelector
    {
        public DataTemplate PropertyIntTemplate { get; set; }
        public DataTemplate PropertyResouceLinkTemplate { get; set; }
        public DataTemplate PropertyUnknownTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            var type = item.GetType();
            if (type.IsGenericType && type.GetGenericTypeDefinition() == typeof(Property<>))
            {
                if (item is Property<int>)
                {
                    return PropertyIntTemplate;
                }
                var propertyType = type.GenericTypeArguments[0];
                if (propertyType.IsGenericType && propertyType.GetGenericTypeDefinition() == typeof(ResourceLink<>))
                {
                    return PropertyResouceLinkTemplate;
                }
            }
            return base.SelectTemplate(item, container);
        }
    }
}
